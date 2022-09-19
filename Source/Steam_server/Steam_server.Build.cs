// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Steam_server : ModuleRules
{
	public Steam_server(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "OnlineSubsystem", "OnlineSubsystemSteam" });
	}
}
