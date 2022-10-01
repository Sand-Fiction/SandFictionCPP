// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SandFictionCPP : ModuleRules
{
	public SandFictionCPP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "GameplayTags" });
    }
}
