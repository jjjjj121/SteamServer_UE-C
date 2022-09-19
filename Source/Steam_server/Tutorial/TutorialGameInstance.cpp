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
		//���� �������̽�
		SessionInterface = SubSystem->GetSessionInterface();

		//���� �������̽� �����ϸ�
		if (SessionInterface.IsValid())
		{
			//Bind Delegates Here
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UTutorialGameInstance::OnCreateSessionComplete);

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
}
