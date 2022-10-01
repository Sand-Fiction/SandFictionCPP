// Copyright Epic Games, Inc. All Rights Reserved.

#include "SandFictionCPP_Editor.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"

IMPLEMENT_GAME_MODULE( FSandFictionCPP_EditorModule, SandFictionCPP_Editor);

DEFINE_LOG_CATEGORY(SandFictionCPP_Editor)

#define LOCTEXT_NAMESPACE "SandFictionCPP_Editor"

void FSandFictionCPP_EditorModule::StartupModule()
{
    UE_LOG(SandFictionCPP_Editor, Warning, TEXT("SandFictionCPP_Editor: Log Started"));
}

void FSandFictionCPP_EditorModule::ShutdownModule()
{
    UE_LOG(SandFictionCPP_Editor, Warning, TEXT("SandFictionCPP_Editor: Log Ended"));
}

#undef LOCTEXT_NAMESPACE
 