// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class SandFictionCPP_EditorTarget : TargetRules
{
	public SandFictionCPP_EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		ExtraModuleNames.Add("SandFictionCPP");
		ExtraModuleNames.Add("SandFictionCPP_Editor");
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
    }
}
