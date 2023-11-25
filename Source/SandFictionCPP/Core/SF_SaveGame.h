// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlowSave.h"
#include "GameplayTagContainer.h"
#include "SandFictionCPP/Components/SF_InventoryComponent.h"
#include "Subsystems/NPCManager/SF_NPCManager.h"
#include "Subsystems/Room/SFRoomSystem.h"
#include "SF_SaveGame.generated.h"

USTRUCT(BlueprintType)
struct FSFSaveData
{
	GENERATED_BODY()

	/// Quest Data

	UPROPERTY(BlueprintReadOnly)
	TArray<FGameplayTag> ActiveQuests;

	UPROPERTY(BlueprintReadOnly)
	TArray<FGameplayTag> CompletedQuests;
	
	/// RoomData
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FSFRoomStruct> Rooms;

	/// CraftingData

	UPROPERTY(BlueprintReadOnly)
	TArray<FGameplayTag> KnownRecipes;

	/// Inventory

	UPROPERTY(BlueprintReadOnly)
	TArray<FInventoryData> CurrentInventory;

	/// NPC WorldStates
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FNPCWorldState> NPCWorldStates;

	/// NPC Dialogues
	
	UPROPERTY(BlueprintReadOnly)
	TMap<FGameplayTag, FGameplayTag> DialogueTags; // NPCTag / DialogueTag

};


UCLASS()
class SANDFICTIONCPP_API USF_SaveGame : public UFlowSaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	FSFSaveData SaveData;

};
