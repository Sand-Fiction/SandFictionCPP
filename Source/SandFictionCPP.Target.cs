// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class SandFictionCPPTarget : TargetRules
{
	public SandFictionCPPTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("SandFictionCPP");
		ExtraModuleNames.Add("SandFictionCPP_Editor");
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
    }
}
