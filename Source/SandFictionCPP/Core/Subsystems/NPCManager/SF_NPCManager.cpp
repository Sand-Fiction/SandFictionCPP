// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_NPCManager.h"

#include "SandFictionCPP/Character/SF_Character_NPC.h"
#include "SandFictionCPP/Data/NPCData.h"

TArray<FNPCWorldState> USF_NPCManager::GetAllNPCWorldStages()
{
	return NPCWorldStates;
}

void USF_NPCManager::Init(UDataTable* NPCDataTable)
{
	// Initialize NPCWorldStates ToDo: Load From SaveGame instead!
	NPCWorldData = NPCDataTable;
	TArray<FNPCData*> AllNPCData;
	NPCWorldData->GetAllRows<FNPCData>("", AllNPCData);
	for (const auto TempNPCData : AllNPCData)
	{
		NPCWorldStates.AddUnique(FNPCWorldState(TempNPCData->GameplayTag, TempNPCData->DefaultWorld));
	}
}

bool USF_NPCManager::GetNPCWorldStageByTag(const FGameplayTag NPCTag, FNPCWorldState &WorldState) const
{
	for (FNPCWorldState TempWorldState  : NPCWorldStates)
	{
		if (TempWorldState.Identifier == NPCTag)
		{
			WorldState = TempWorldState;
			return true;
		}
	}

	return false;
}

bool USF_NPCManager::GetNPCDataByTag(const FGameplayTag NPCTag, FNPCData& OutNPCData) const
{
	// Get Default NPCData of DataTable
	TArray<FNPCData*> AllNPCData;
	NPCWorldData->GetAllRows<FNPCData>("", AllNPCData);
	
	// Iterate all NPCs and compare Tag
	for (const auto NPCData : AllNPCData)
	{
		if (NPCData->GameplayTag == NPCTag)
		{
			OutNPCData = *NPCData;
			return true;
		}
	}
	return false;
}

void USF_NPCManager::SetNPCWorld(const FGameplayTag NPCTag, const FGameplayTag WorldTag)
{
	const FNPCWorldState NewWorldState = FNPCWorldState(NPCTag, WorldTag);

	NPCWorldStates.Remove(NPCTag);
	NPCWorldStates.AddUnique(NewWorldState);

	OnNPCWorldStateChange.Broadcast(NewWorldState);
}

void USF_NPCManager::SpawnAllNPCsInWorld(const FGameplayTag WorldTag)
{
	// Iterate all NPCs and check if they belong to this World
	for (const auto NPCWorldState : NPCWorldStates)
	{
		if (NPCWorldState.World == WorldTag)
		{
			FNPCData NPCData;
			if (GetNPCDataByTag(NPCWorldState.Identifier, NPCData))
			{
				SpawnNPC(NPCData, WorldTag);
			}
		}
	}
}

void USF_NPCManager::SpawnNPC(FNPCData NPCData, const FGameplayTag WorldTag) const
{
	if (NPCData.WorldSpawnPositions.Contains(WorldTag) && NPCData.WorldSpawnPositions.Find(WorldTag)->IsValid())
	{
		const auto TransformActor = NPCData.WorldSpawnPositions.Find(WorldTag)->LoadSynchronous();
		const FTransform SpawnTransform = TransformActor->GetTransform();
		if (ASF_Character_NPC* NPC = GetWorld()->SpawnActorDeferred<ASF_Character_NPC>(NPCData.ActorClass, SpawnTransform))
		{
			// ToDo: Do not use Default Dialogue but rather NPCSaveGameData
			NPC->Dialogue = NPCData.DefaultDialogue;
			NPC->FinishSpawning(SpawnTransform);
			
			UE_LOG(LogTemp, Warning, TEXT("Successfully spawned NPC %s!"), *NPCData.Name.ToString());
			return;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("NPC %s could not be spawned!"), *NPCData.Name.ToString());
}
