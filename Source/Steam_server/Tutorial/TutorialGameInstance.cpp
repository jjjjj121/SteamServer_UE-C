// Fill out your copyright notice in the Description page of Project Settings.


#include "Steam_server/Tutorial/TutorialGameInstance.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"


UTutorialGameInstance::UTutorialGameInstance()
{

}

void UTutorialGameInstance::Init()
{

	if (IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get())
	{
		//세션 인터페이스
		SessionInterface = SubSystem->GetSessionInterface();

		//세션 인터페이스 존재하면
		if (SessionInterface.IsValid())
		{
			//Bind Delegates Here
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UTutorialGameInstance::OnCreateSessionComplete);

			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UTutorialGameInstance::OnFindSessionComplete);
			
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UTutorialGameInstance::OnJoinSessionComplete);


			UE_LOG(LogTemp, Warning, TEXT("Bind Delegates"));

		}

	}

}
	 
void UTutorialGameInstance::OnCreateSessionComplete(FName ServerName, bool Succeeded)
{
	UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionComplete, Succeeded: %d"), Succeeded);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("OnCreateSessionComplete, Succeeded: %d"), Succeeded);

	if (Succeeded)
	{
		GetWorld()->ServerTravel("/Game/FirstPersonCPP/Maps/FirstPersonExampleMap?listen");
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Succeeded Create Session"));

	}

}

void UTutorialGameInstance::OnFindSessionComplete(bool Succeeded)
{
	UE_LOG(LogTemp, Warning, TEXT("OnFindSessionComplete, Succeeded: %d"), Succeeded);
	if(Succeeded)
	{
		TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;

		UE_LOG(LogTemp, Warning, TEXT("SearchResults, Server Count: %d"), SearchResults.Num());

		if (SearchResults.Num())
		{
			UE_LOG(LogTemp, Warning, TEXT("Joining Server"));
			SessionInterface->JoinSession(0, "My Session", SearchResults[0]);

		}


	}
}

void UTutorialGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	UE_LOG(LogTemp, Warning, TEXT("OnJoinSessionComplete, SessionName: %s"), *SessionName.ToString());

	if (APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		FString JoinAddress = "";
		SessionInterface->GetResolvedConnectString(SessionName, JoinAddress);
		if (JoinAddress != "")
		{
			PController->ClientTravel(JoinAddress, ETravelType::TRAVEL_Absolute);
		}
		
	}


}


void UTutorialGameInstance::CreateServer()
{
	UE_LOG(LogTemp, Warning, TEXT("CreateServer"));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("CreateServer"));

	FOnlineSessionSettings SessionSettings;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = false;
	if (IOnlineSubsystem::Get()->GetSubsystemName() != "NULL")
		SessionSettings.bIsLANMatch = false;
	else
		SessionSettings.bIsLANMatch = true; //Is LAN

	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.NumPublicConnections = 5;


	SessionInterface->CreateSession(0, FName("My Session"), SessionSettings);
}

void UTutorialGameInstance::JoinServer()
{

	UE_LOG(LogTemp, Warning, TEXT("JoinServer"));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("JoinServer"));


	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (IOnlineSubsystem::Get()->GetSubsystemName() != "NULL")
		SessionSearch->bIsLanQuery = false; 
	else
		SessionSearch->bIsLanQuery = true; //Is LAN
	SessionSearch->MaxSearchResults = 10000;
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);



	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());


}
