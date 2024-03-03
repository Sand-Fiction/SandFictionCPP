// Fill out your copyright notice in the Description page of Project Settings.


#include "FlowGraphNode_Checkpoint.h"

#include "FlowSave.h"
#include "FlowSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "SandFictionCPP/Core/SF_GameInstance.h"

UFlowGraphNode_Checkpoint::UFlowGraphNode_Checkpoint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Utils");
#endif
}

void UFlowGraphNode_Checkpoint::ExecuteInput(const FName& PinName)
{
	// Save Flow Data
	if (GetFlowSubsystem())
	{
		UFlowSaveGame* NewSaveGame = Cast<UFlowSaveGame>(UGameplayStatics::CreateSaveGameObject(UFlowSaveGame::StaticClass()));
		GetFlowSubsystem()->OnGameSaved(NewSaveGame);

		UGameplayStatics::SaveGameToSlot(NewSaveGame, NewSaveGame->SaveSlotName, 0);
	}

	// Save SandFiction Data
	if (GetWorld())
	{
		if (const auto GameInstance = Cast<USF_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
		{
			GameInstance->SaveGame();
		}
	}

	TriggerFirstOutput(true);
}

void UFlowGraphNode_Checkpoint::OnLoad_Implementation()
{
	TriggerFirstOutput(true);
}
