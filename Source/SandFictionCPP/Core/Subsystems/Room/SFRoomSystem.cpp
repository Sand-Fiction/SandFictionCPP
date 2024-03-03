// Fill out your copyright notice in the Description page of Project Settings.


#include "SFRoomSystem.h"

#include "AsyncTreeDifferences.h"
#include "Kismet/GameplayStatics.h"
#include "SandFictionCPP/Components/SF_RecipeBookComponent.h"

TArray<FSFRoomActorStruct> FSFRoomStruct::GetAllActorStructsWithTag(FGameplayTag ActorTag)
{
	TArray<FSFRoomActorStruct> ReturnArray;
	for (const auto ActorStruct: BuildActors)
	{
		if (ActorStruct.Identifier == ActorTag)
		{
			ReturnArray.Add(ActorStruct);
		}
	}

	return ReturnArray;
}

bool FSFRoomStruct::IsBuildLimitReached(int32& FreeSpace) const
{
	FreeSpace = MaxBuildActors - BuildActors.Num();
	return BuildActors.Num() >= MaxBuildActors;
}

void USFRoomSystem::Init(UDataTable* RoomDataTable, UDataTable* RecipeDataTable)
{
	RecipeDT = RecipeDataTable;
	RoomDT = RoomDataTable;

	TArray<FSFRoomStruct*> TempRoomArray;
	RoomDT->GetAllRows<FSFRoomStruct>("", TempRoomArray);

	for (const auto TempRoom : TempRoomArray)
	{
		Rooms.AddUnique(*TempRoom);
	}
}

void USFRoomSystem::InitializeActorsInRoom (FGameplayTag RoomTag)
{
	if (!GetWorld())
	{
		return;
	}

	FSFRoomStruct RoomData;
	if (GetRoomDataByTag(RoomTag, RoomData))
	{
		for (auto ActorData : RoomData.BuildActors)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			const auto Actor = GetWorld()->SpawnActor(ActorData.ActorClass, &ActorData.Transform, SpawnParams);
			ActorData.ActorSoftReference = Actor;
		}
	}
}

 bool USFRoomSystem::GetRoomDataByTag(const FGameplayTag RoomTag, FSFRoomStruct& RoomData) const
{
	for (const auto Room : Rooms)
	{
		if (Room.RoomIdentifier == RoomTag)
		{
			RoomData = Room;
			return true;
		}
	}

	return false;
}

bool USFRoomSystem::IsRoomStageCompleted(const FGameplayTag RoomTag, const int32 StageIndex)
{
	for (const auto Room : Rooms)
	{
		if (Room.RoomIdentifier == RoomTag && Room.CurrentStageIndex >= StageIndex)
		{
			return true;
		}
	}

	return false;
}

void USFRoomSystem::TryCompleteRoomStage(FGameplayTag RoomTag)
{
	FSFRoomStruct RoomData;
	if (GetRoomDataByTag(RoomTag, RoomData))
	{
		if (RoomData.Stages.IsValidIndex(RoomData.CurrentStageIndex))
		{
			// Iterate all needed Actors and check if enough;
			FSFRoomStageStruct CurrentStageData = RoomData.Stages[RoomData.CurrentStageIndex];
			bool ReturnValue = true;
			for (const auto NeededActor : CurrentStageData.NeededBuildActors)
			{
				int32 ActorQuantity = 0;
				for (const auto BuildActorData : RoomData.BuildActors)
				{
					if (BuildActorData.Identifier == NeededActor.Key)
					{
						ActorQuantity++;
					}
				}
				
				ActorQuantity < NeededActor.Value ? ReturnValue = false : ReturnValue = true;

				// Already break if one of the needed Actors is not in the room with the needed quantity
				if (!ReturnValue)
				{
					break;
				}
			}

			// Update CurrentStageIndex if RoomStage is complete
			if (ReturnValue)
			{
				FSFRoomStruct TempRoom;
				for (const auto Room : Rooms)
				{
					if (Room.RoomIdentifier == RoomTag)
					{
						TempRoom = Room;
					}
				}
				Rooms[Rooms.Find(TempRoom)].CurrentStageIndex++;
			}
		}
	}
}

bool USFRoomSystem::AddActorToRoom(FGameplayTag RoomTag, FSFRoomActorStruct ActorStruct)
{
	FSFRoomStruct RoomData;
	if (GetRoomDataByTag(RoomTag, RoomData))
	{
		int32 FreeSpace;
		if (!RoomData.IsBuildLimitReached(FreeSpace))
		{
			RoomData.BuildActors.AddUnique(ActorStruct);
			Rooms.Remove(RoomData);
			Rooms.AddUnique(RoomData);

			TryCompleteRoomStage(RoomTag);
			
			if (IsRoomStageCompleted(RoomTag, RoomData.CurrentStageIndex))
			{
				OnRoomStageFinished.Broadcast(RoomTag);
			}

			OnActorAddedToRoom.Broadcast(RoomTag, ActorStruct);

			return true;
		}	
	}
	return false;
}

void USFRoomSystem::RemoveActorFromRoom(FGameplayTag RoomTag, FSFRoomActorStruct ActorStruct)
{
	FSFRoomStruct RoomData;
	if (GetRoomDataByTag(RoomTag, RoomData))
	{
		FSFRoomActorStruct ActorToRemove;
		for (const auto BuildActor : RoomData.BuildActors)
		{
			if (BuildActor == ActorStruct)
			{
				ActorToRemove = BuildActor;

				RoomData.BuildActors.Remove(ActorToRemove);
				Rooms.Remove(RoomData);
				Rooms.AddUnique(RoomData);

				OnActorRemovedFromRoom.Broadcast(RoomTag, ActorStruct);

				break;
			}
		}
	}	
}

TSubclassOf<AActor> USFRoomSystem::GetBuildActorClassByTag(FGameplayTag ActorTag) const
{
	TArray<FCraftingRecipe*> CraftingRecipes;
	RecipeDT->GetAllRows<FCraftingRecipe>("", CraftingRecipes);

	for (const auto Recipe: CraftingRecipes)
	{
		if (*Recipe == ActorTag)
		{
			return Recipe->ItemClass;
		}
	}

	return nullptr;
}
