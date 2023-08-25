// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;



public class SandFictionCPP_Editor : ModuleRules
{
	public SandFictionCPP_Editor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "SandFictionCPP" });

        PrivateDependencyModuleNames.AddRange(new string[]
        {

            "Core",
            "CoreUObject",
            "Engine",
            
            "UnrealEd",
            "FlowEditor",
            "GraphEditor",
            "KismetWidgets",
            "EditorStyle",

            "InputCore",
            "Flow",
            "Slate",
            "SlateCore",
        });

    }
}
