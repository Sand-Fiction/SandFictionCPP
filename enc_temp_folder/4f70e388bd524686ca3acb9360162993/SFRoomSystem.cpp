// Fill out your copyright notice in the Description page of Project Settings.


#include "SFRoomSystem.h"

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

 bool USFRoomSystem::GetRoomDataByTag(FGameplayTag RoomTag, FSFRoomStruct& RoomData) const
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

bool USFRoomSystem::IsRoomStageCompleted(FGameplayTag RoomTag, int32 StageIndex)
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
		RoomData.BuildActors.Remove(ActorStruct);
	}

	Rooms.Remove(RoomData);
	Rooms.AddUnique(RoomData);
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
