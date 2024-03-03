// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_GameInstance.h"

#include "FlowSubsystem.h"
#include "SF_SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "SandFictionCPP/Character/SF_Character_Main.h"
#include "SandFictionCPP/Components/SF_RecipeBookComponent.h"
#include "Subsystems/Quest/SFQuestSystem.h"
#include "Subsystems/Room/SFRoomSystem.h"

void USF_GameInstance::SaveGame_Implementation()
{
	// Gather Subsystems
	const auto NPCManager = GetSubsystem<USF_NPCManager>();
	const auto FlowSubsystem = GetSubsystem<UFlowSubsystem>();
	const auto RoomSystem = GetSubsystem<USFRoomSystem>();
	const auto QuestSystem = GetSubsystem<USFQuestSystem>();

	// Check SaveGameObject and create if necessary
	if (!SaveGameObject)
	{
		SaveGameObject = Cast<USF_SaveGame>(UGameplayStatics::CreateSaveGameObject(USF_SaveGame::StaticClass()));
		SaveGameObject->SaveData = {};
	}

	// Gather RoomData
	if (RoomSystem)
	{
		SaveGameObject->SaveData.Rooms = RoomSystem->Rooms;
	}

	// Gather QuestData
	if (QuestSystem)
	{
		SaveGameObject->SaveData.ActiveQuests = QuestSystem->ActiveQuests;
		SaveGameObject->SaveData.CompletedQuests = QuestSystem->CompletedQuests;
	}

	// Gather Inventory & Recipes of Player
	if (const auto World = GetWorld())
	{
		if (const auto Player = Cast<ASF_Character_Main>(UGameplayStatics::GetPlayerCharacter(World, 0)))
		{
			if (const USF_InventoryComponent* Inventory = Player->GetInventoryComponent())
			{
				SaveGameObject->SaveData.CurrentInventory = Inventory->GetInventory();
			}

			if (const USF_RecipeBookComponent* RecipeBook = Player->GetRecipeBookComponent())
			{
				SaveGameObject->SaveData.KnownRecipes = RecipeBook->KnownRecipes;
			}
		}
	}

	// Gather NPC WorldStates
	if (NPCManager)
	{
		SaveGameObject->SaveData.NPCWorldStates = NPCManager->NPCWorldStates;
	}

	// Gather NPC Dialogues
	if (NPCManager && FlowSubsystem)
	{
		for (const auto NPCWorldState : NPCManager->NPCWorldStates)
		{
			const auto NPCsWithTag = FlowSubsystem->GetFlowActorsByTag(NPCWorldState.Identifier, ASF_Character_NPC::StaticClass());
			// Only check first Actor with Tag because usually there should always only be one NPC with the same Tag
			if (NPCsWithTag.Array().IsValidIndex(0))
			{
				if (const auto NPC = Cast<ASF_Character_NPC>(NPCsWithTag.Array()[0]))
				{
					SaveGameObject->SaveData.DialogueTags.Emplace(NPCWorldState.Identifier, NPC->Dialogue);
				}
			}
		}
	}

	UGameplayStatics::SaveGameToSlot(SaveGameObject, "SandFiction", 0);
}

void USF_GameInstance::LoadGame_Implementation()
{
	if (!UGameplayStatics::DoesSaveGameExist("SandFiction", 0))
	{
		return;
	}

	SaveGameObject = Cast<USF_SaveGame>(UGameplayStatics::LoadGameFromSlot("SandFiction", 0));

	if (!SaveGameObject)
	{
		return;
	}

	// Apply RoomData
	if (const auto RoomSystem = GetSubsystem<USFRoomSystem>())
	{
		RoomSystem->Rooms = SaveGameObject->SaveData.Rooms;
	}

	// Apply QuestData
	if (const auto QuestSystem = GetSubsystem<USFQuestSystem>())
	{
		QuestSystem->ActiveQuests = SaveGameObject->SaveData.ActiveQuests;
		QuestSystem->CompletedQuests = SaveGameObject->SaveData.CompletedQuests;
	}

	// Apply Inventory & Recipes
	if (const auto World = GetWorld())
	{
		if (const auto Player = Cast<ASF_Character_Main>(UGameplayStatics::GetPlayerCharacter(World, 0)))
		{
			if (USF_InventoryComponent* Inventory = Player->GetInventoryComponent())
			{
				Inventory->CurrentInventory = SaveGameObject->SaveData.CurrentInventory;
			}

			if (USF_RecipeBookComponent* RecipeBook = Player->GetRecipeBookComponent())
			{
				RecipeBook->KnownRecipes = SaveGameObject->SaveData.KnownRecipes;
			}
		}
	}

	// Apply NPC WorldState Data
	if (const auto NPCManager = GetSubsystem<USF_NPCManager>())
	{
		NPCManager->NPCWorldStates = SaveGameObject->SaveData.NPCWorldStates;
	}
}

void USF_GameInstance::DeleteGame_Implementation()
{
	UGameplayStatics::DeleteGameInSlot("SandFiction", 0);
}

bool USF_GameInstance::DoesSaveGameExist()
{
	return UGameplayStatics::DoesSaveGameExist("SandFiction", 0);
}

bool USF_GameInstance::IsSaveGameLoaded() const
{
	return SaveGameObject != nullptr;
}

USF_SaveGame* USF_GameInstance::GetSaveGameObject() const
{
	return SaveGameObject;
}
