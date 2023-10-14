// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_NPCManager.h"

#include "SandFictionCPP/Data/NPCData.h"

TArray<FNPCWorldState> USF_NPCManager::GetAllNPCWorldStages()
{
	return NPCWorldStates;
}

void USF_NPCManager::Init(UDataTable* NPCDataTable)
{
	NPCData = NPCDataTable;

	TArray<FNPCData*> AllNPCData;
	NPCData->GetAllRows<FNPCData>("", AllNPCData);

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

void USF_NPCManager::SetNPCWorld(FGameplayTag NPCTag, FGameplayTag WorldTag)
{
	const FNPCWorldState NewWorldState = FNPCWorldState(NPCTag, WorldTag);

	NPCWorldStates.Remove(NPCTag);
	NPCWorldStates.AddUnique(NewWorldState);

	OnNPCWorldStateChange.Broadcast(NewWorldState);
}
