// Fill out your copyright notice in the Description page of Project Settings.


#include "SFQuestSystem.h"

#include "Kismet/GameplayStatics.h"
#include "SandFictionCPP/Core/Subsystems/Room/SFRoomSystem.h"

void USFQuestSystem::Init(UDataTable* QuestData)
{
	QuestDT = QuestData;
}

void USFQuestSystem::AddQuest(FGameplayTag QuestTag)
{
	ActiveQuests.AddUnique(QuestTag);
}

void USFQuestSystem::TryCompleteQuest(FGameplayTag QuestTag)
{
	if (CanCompleteQuest(QuestTag))
	{
		ActiveQuests.Remove(QuestTag);
		CompletedQuests.AddUnique(QuestTag);
	}
}

bool USFQuestSystem::GetQuestDataByTag(FGameplayTag QuestTag, FSFQuestStruct& Data) const
{
	if (!QuestDT)
	{
		return false;
	}

	TArray<FSFQuestStruct*> RowStructs;
	QuestDT->GetAllRows<FSFQuestStruct>("", RowStructs);
	for (const auto Struct : RowStructs)
	{
		if (Struct->RoomIdentifier == QuestTag)
		{
			Data = *Struct;
			return true;
		}
	}

	return false;
}

bool USFQuestSystem::CanCompleteQuest(FGameplayTag QuestTag) const
{
	const auto GameInstance = UGameplayStatics::GetGameInstance(this);
	const auto RoomSystem = GameInstance->GetSubsystem<USFRoomSystem>();

	if (!RoomSystem)
	{
		return false;
	}

	FSFQuestStruct QuestData;
	if (GetQuestDataByTag(QuestTag, QuestData))
	{
		return RoomSystem->IsRoomStageCompleted(QuestData.RoomIdentifier, QuestData.RoomStageTargetIndex);
	}

	return false;
}
