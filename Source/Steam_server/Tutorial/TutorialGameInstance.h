// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "TutorialGameInstance.generated.h"

/**
 * 
 */

UCLASS()
class STEAM_SERVER_API UTutorialGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:

	UTutorialGameInstance();


protected:
	IOnlineSessionPtr SessionInterface;

	TSharedPtr<FOnlineSessionSearch> SessionSearch;


protected:
	virtual void Init() override;

	virtual void OnCreateSessionComplete(FName ServerName, bool Succeeded);
	
	virtual void OnFindSessionComplete(bool Succeeded);

	virtual void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

protected:
	UFUNCTION(BlueprintCallable)
		void CreateServer();

	UFUNCTION(BlueprintCallable)
		void JoinServer();


};
