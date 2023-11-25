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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag QuestIdentifier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag RoomIdentifier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 RoomStageTargetIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* Icon;

	bool IsValid() const
	{
		return RoomIdentifier.IsValid();
	}

	FSFQuestStruct(): RoomStageTargetIndex(0), Icon(nullptr)
	{
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestEvent, const FGameplayTag, QuestTag);

UCLASS(DisplayName = QuestSystem)
class SANDFICTIONCPP_API USFQuestSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	UPROPERTY()
	UDataTable* QuestDT;

public:
	
	UFUNCTION(BlueprintCallable)
	void Init(UDataTable* QuestData);

	UPROPERTY(BlueprintReadWrite)
	TArray<FGameplayTag> ActiveQuests;

	UPROPERTY(BlueprintReadWrite)
	TArray<FGameplayTag> CompletedQuests;

	UFUNCTION(BlueprintCallable)
	void AddQuest(FGameplayTag QuestTag);

	UFUNCTION(BlueprintCallable)
	bool TryCompleteQuest(FGameplayTag QuestTag);

	UFUNCTION(BlueprintPure)
	bool GetQuestDataByTag(FGameplayTag QuestTag, FSFQuestStruct& QuestData) const;

	UFUNCTION(BlueprintPure)
	TArray<FGameplayTag> GetAllQuestTagsForRoom(FGameplayTag RoomTag);

	UFUNCTION(BlueprintPure)
	bool CanCompleteQuest(FGameplayTag QuestTag) const;

	UFUNCTION()
	void OnRoomStageFinished(FGameplayTag RoomTag);

	UPROPERTY(BlueprintAssignable)
	FOnQuestEvent OnQuestAdded;

	UPROPERTY(BlueprintAssignable)
	FOnQuestEvent OnQuestCompleted;
	
};
