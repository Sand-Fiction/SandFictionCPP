// Fill out your copyright notice in the Description page of Project Settings.


#include "SFQuestSystem.h"

#include "Kismet/GameplayStatics.h"
#include "SandFictionCPP/Core/Subsystems/Room/SFRoomSystem.h"

void USFQuestSystem::Init(UDataTable* QuestData)
{
	QuestDT = QuestData;

	if (const auto RoomSystem = GetGameInstance()->GetSubsystem<USFRoomSystem>())
	{
		RoomSystem->OnRoomStageFinished.AddDynamic(this, &USFQuestSystem::OnRoomStageFinished);
	}
}

void USFQuestSystem::AddQuest(const FGameplayTag QuestTag)
{
	ActiveQuests.AddUnique(QuestTag);
	OnQuestAdded.Broadcast(QuestTag);
}

void USFQuestSystem::TryCompleteQuest(const FGameplayTag QuestTag)
{
	if (CanCompleteQuest(QuestTag))
	{
		ActiveQuests.Remove(QuestTag);
		CompletedQuests.AddUnique(QuestTag);
		OnQuestCompleted.Broadcast(QuestTag);
	}
}

bool USFQuestSystem::GetQuestDataByTag(const FGameplayTag QuestTag, FSFQuestStruct& QuestData) const
{
	if (!QuestDT)
	{
		return false;
	}

	TArray<FSFQuestStruct*> RowStructs;
	QuestDT->GetAllRows<FSFQuestStruct>("", RowStructs);
	for (const auto Struct : RowStructs)
	{

		if (Struct->QuestIdentifier == QuestTag)
		{
			QuestData = *Struct;
			return true;
		}
	}

	return false;
}

TArray<FGameplayTag> USFQuestSystem::GetAllQuestTagsForRoom(const FGameplayTag RoomTag)
{
	TArray<FGameplayTag> QuestsForRoom;
	for (const auto QuestTag : ActiveQuests)
	{
		FSFQuestStruct QuestData;
		if (GetQuestDataByTag(QuestTag, QuestData))
		{
			if (QuestData.RoomIdentifier == RoomTag)
			{
				QuestsForRoom.AddUnique(QuestTag);
			}
		}
	}

	return QuestsForRoom;
}

bool USFQuestSystem::CanCompleteQuest(const FGameplayTag QuestTag) const
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

void USFQuestSystem::OnRoomStageFinished(const FGameplayTag RoomTag)
{
	// Try to complete all active quests, that are part of that Room
	TArray<FGameplayTag> QuestsForRoom = GetAllQuestTagsForRoom(RoomTag);
	for (const auto QuestTag : QuestsForRoom)
	{
		TryCompleteQuest(QuestTag);
	}
}