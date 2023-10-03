// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlowSave.h"
#include "GameplayTagContainer.h"
#include "Subsystems/Room/SFRoomSystem.h"
#include "SF_SaveGame.generated.h"

USTRUCT(BlueprintType)
struct FSFSaveData
{
	GENERATED_BODY()

	/// Quest Data

	UPROPERTY(SaveGame, BlueprintReadWrite)
	TArray<FGameplayTag> ActiveQuests;

	UPROPERTY(SaveGame, BlueprintReadWrite)
	TArray<FGameplayTag> CompletedQuests;


	/// RoomData
	
	UPROPERTY(SaveGame, BlueprintReadWrite)
	TArray<FSFRoomStruct> Rooms;

	/// CraftingData

	UPROPERTY(SaveGame, BlueprintReadWrite)
	TArray<FGameplayTag> KnownRecipes;

	/**
	 * ToDo: Gather all Properties, that need to be saved!
	 *
	 * ToDo: Recipes?
	 * ToDo: Inventory?
	 *
	 * ToDo: UFlowSystem	- Dialogues (Rest should be handled already)
	 *
	 * ToDo: NPCs on Earth / Ship?
	 *
	 */

};


UCLASS()
class SANDFICTIONCPP_API USF_SaveGame : public UFlowSaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	FSFSaveData SaveData;

};
