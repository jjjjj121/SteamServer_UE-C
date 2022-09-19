// Fill out your copyright notice in the Description page of Project Settings.


#include "Steam_server/Tutorial/TutorialGameInstance.h"

#include "Engine/World.h"
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

			SessionInterface->OnCancelFindSessionsCompleteDelegates.AddUObject(this, &UTutorialGameInstance::OnFindSessionComplete);


		}

	}

}

void UTutorialGameInstance::OnCreateSessionComplete(FName ServerName, bool Succeeded)
{
	UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionComplete, Succeeded: %d"), Succeeded);

	if (Succeeded)
	{
		GetWorld()->ServerTravel("/Game/FirstPersonCPP/Maps/FirstPersonExampleMap?listen");
	}

}

void UTutorialGameInstance::OnFindSessionComplete(bool Succeeded)
{
	UE_LOG(LogTemp, Warning, TEXT("OnFindSessionComplete, Succeeded: %d"), Succeeded);
	if(Succeeded)
	{
		TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;
		UE_LOG(LogTemp, Warning, TEXT("SearchResults, Server Count: %d"), SearchResults.Num());

	}

}


void UTutorialGameInstance::CreateServer()
{
	UE_LOG(LogTemp, Warning, TEXT("CreateServer"));

	FOnlineSessionSettings SessionSettings;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bIsLANMatch = true;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.NumPublicConnections = 5;


	SessionInterface->CreateSession(0, FName("My Session"), SessionSettings);
}

void UTutorialGameInstance::JoinServer()
{

	UE_LOG(LogTemp, Warning, TEXT("JoinServer"));



	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery = true; //Is LAN
	SessionSearch->MaxSearchResults = 10000;
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);



	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());


}
