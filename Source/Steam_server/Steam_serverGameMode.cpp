// Copyright Epic Games, Inc. All Rights Reserved.

#include "Steam_serverGameMode.h"
#include "Steam_serverHUD.h"
#include "Steam_serverCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASteam_serverGameMode::ASteam_serverGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ASteam_serverHUD::StaticClass();
}
