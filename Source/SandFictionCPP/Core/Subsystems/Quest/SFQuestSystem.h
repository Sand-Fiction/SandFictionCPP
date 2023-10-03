// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SFQuestSystem.generated.h"

USTRUCT(BlueprintType)
struct FSFQuestStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FGameplayTag QuestIdentifier;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FGameplayTag RoomIdentifier;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 RoomStageTargetIndex;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName Name;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText Description;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UTexture2D* Icon;

	bool IsValid() const
	{
		return RoomIdentifier.IsValid();
	}

	FSFQuestStruct()
	{
		QuestIdentifier = FGameplayTag();
		RoomIdentifier = FGameplayTag();
		RoomStageTargetIndex = 0;
		Name = TEXT("QuestName");
		Description = FText::FromString("");
		Icon = nullptr;
	}
};


UCLASS()
class SANDFICTIONCPP_API USFQuestSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	UDataTable* QuestDT;

public:

	UFUNCTION(BlueprintCallable)
	void Init(UDataTable* QuestData, TArray<FGameplayTag> ActiveQuestArray, TArray<FGameplayTag> CompletedQuestArray);

	UPROPERTY(BlueprintReadOnly)
	TArray<FGameplayTag> ActiveQuests;

	UPROPERTY(BlueprintReadOnly)
	TArray<FGameplayTag> CompletedQuests;

	UFUNCTION(BlueprintCallable)
	void AddQuest(FGameplayTag QuestTag);

	UFUNCTION(BlueprintCallable)
	void TryCompleteQuest(FGameplayTag QuestTag);

	UFUNCTION(BlueprintPure)
	bool GetQuestDataByTag(FGameplayTag QuestTag, FSFQuestStruct& Data) const;

	UFUNCTION(BlueprintPure)
	bool CanCompleteQuest(FGameplayTag QuestTag) const;
	
};
