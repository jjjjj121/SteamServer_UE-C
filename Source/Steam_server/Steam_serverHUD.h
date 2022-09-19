// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Steam_serverHUD.generated.h"

UCLASS()
class ASteam_serverHUD : public AHUD
{
	GENERATED_BODY()

public:
	ASteam_serverHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

