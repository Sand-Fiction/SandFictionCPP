// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "Engine/TargetPoint.h"
#include "SandFictionCPP/Character/SF_Character_NPC.h"
#include "NPCData.generated.h"



UENUM(BlueprintType)
enum class EDialogueType : uint8
{
	E_Dialogue_Main UMETA(DisplayName = "Main"),
	E_Dialogue_Side UMETA(DisplayName = "Side"),
};

USTRUCT(BlueprintType)
struct FNPCData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor NodeColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag GameplayTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag DefaultWorld;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGameplayTag, TSoftObjectPtr<ATargetPoint>> WorldSpawnPositions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag DefaultDialogue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ASF_Character_NPC> ActorClass;

	FNPCData()
	{
		Name = FText::FromString("NPC Name");
		Description = FText::FromString("NPC Description");
		NodeColor = FColor::White;
	}

};

