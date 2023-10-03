// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SFRoomSystem.generated.h"

USTRUCT(BlueprintType)
struct FSFRoomActor
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag Identifier;

	UPROPERTY(BlueprintReadOnly)
	FTransform Transform;

	UPROPERTY(BlueprintReadOnly)
	TSubclassOf<AActor> ActorClass;

	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<AActor> ActorSoftReference;

	bool operator== (const FSFRoomActor& Other) const
	{
		return Identifier == Other.Identifier && ActorSoftReference == Other.ActorSoftReference;
	}

	FSFRoomActor()
	{
		
	}

	FSFRoomActor(FGameplayTag Identifier, FTransform Transform, TSubclassOf<AActor> ActorClass)
	{
		this->Identifier = Identifier;
		this->Transform = Transform;
		this->ActorClass = ActorClass;
	}

	FSFRoomActor(FGameplayTag Identifier, FTransform Transform, TSubclassOf<AActor> ActorClass, TSoftObjectPtr<AActor> ActorSoftReference)
	{
		this->Identifier = Identifier;
		this->Transform = Transform;
		this->ActorClass = ActorClass;
		this->ActorSoftReference = ActorSoftReference;
	}
};

USTRUCT(BlueprintType)
struct FSFRoomStageStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<FGameplayTag, int32> NeededBuildActors;
	
};

USTRUCT(BlueprintType)
struct FSFRoomStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FGameplayTag RoomIdentifier;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<FGameplayTag> NPCs;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<FSFRoomStageStruct> Stages;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 CurrentStageIndex;

	UPROPERTY()
	TArray<FSFRoomActor> BuildActors;

	TArray<FSFRoomActor> GetAllActorStructsWithTag(FGameplayTag ActorTag);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 MaxBuildActors;

	bool IsBuildLimitReached(int32& FreeSpace);
};


UCLASS()
class SANDFICTIONCPP_API USFRoomSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	UDataTable* RoomDT;

	UPROPERTY()
	UDataTable* RecipeDT;

public:

	UFUNCTION(BlueprintCallable)
	void Init(UDataTable* RoomDataTable, UDataTable* BuildActorsDataTable, TArray<FSFRoomStruct> RoomsData);

	UPROPERTY(BlueprintReadOnly)
	TArray<FSFRoomStruct> Rooms;

	UFUNCTION(BlueprintCallable)
	void InitializeActorsInRoom(FGameplayTag RoomTag);

	UFUNCTION(BlueprintPure)
	bool GetRoomDataByTag(FGameplayTag RoomTag, FSFRoomStruct& RoomData) const;

	UFUNCTION(BlueprintPure)
	bool IsRoomStageCompleted(FGameplayTag RoomTag, int32 StageIndex);

	UFUNCTION(BlueprintCallable)
	void AddActorToRoom(FGameplayTag RoomTag, FSFRoomActor ActorStruct, int32 Quantity = 1);

	UFUNCTION(BlueprintCallable)
	void RemoveActorFromRoom(FGameplayTag RoomTag, FSFRoomActor ActorStruct, int32 Quantity = 1);

	UFUNCTION(BlueprintPure)
	TSubclassOf<AActor> GetBuildActorClassByTag(FGameplayTag ActorTag) const;

};
