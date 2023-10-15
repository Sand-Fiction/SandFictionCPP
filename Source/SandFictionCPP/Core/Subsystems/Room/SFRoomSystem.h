// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SFRoomSystem.generated.h"

USTRUCT(BlueprintType)
struct FSFRoomActorStruct
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

	bool operator== (const FSFRoomActorStruct& Other) const
	{
		return Identifier == Other.Identifier && ActorSoftReference == Other.ActorSoftReference;
	}

	FSFRoomActorStruct()
	{
		
	}

	FSFRoomActorStruct(FGameplayTag Identifier, const TSoftObjectPtr<AActor>& ActorSoftReference)
	{
		this->Identifier = Identifier;
		this->ActorSoftReference = ActorSoftReference;
	}

	FSFRoomActorStruct(FGameplayTag Identifier, const FTransform& Transform, const TSubclassOf<AActor> ActorClass)
	{
		this->Identifier = Identifier;
		this->Transform = Transform;
		this->ActorClass = ActorClass;
	}

	FSFRoomActorStruct(FGameplayTag Identifier, FTransform Transform, TSubclassOf<AActor> ActorClass, TSoftObjectPtr<AActor> ActorSoftReference)
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
	int32 CurrentStageIndex = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSoftObjectPtr<AActor> ActorSoftReference;

	UPROPERTY(BlueprintReadOnly)
	TArray<FSFRoomActorStruct> BuildActors;

	TArray<FSFRoomActorStruct> GetAllActorStructsWithTag(FGameplayTag ActorTag);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 MaxBuildActors = 8;
	
	bool IsBuildLimitReached(int32& FreeSpace) const;

	bool operator== (const FSFRoomStruct &Other) const
	{
		return RoomIdentifier == Other.RoomIdentifier;
	}

	bool operator== (const FGameplayTag& Other) const
	{
		return RoomIdentifier == Other;
	}	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRoomEvent, FGameplayTag, RoomTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRoomActorEvent, FGameplayTag, RoomTag, FSFRoomActorStruct, ActorStruct);

UCLASS(DisplayName = RoomSystem)
class SANDFICTIONCPP_API USFRoomSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	UDataTable* RoomDT;

	UPROPERTY()
	UDataTable* RecipeDT;

public:

	UFUNCTION(BlueprintCallable)
	void Init(UDataTable* RoomDataTable, UDataTable* RecipeDataTable);

	UPROPERTY(BlueprintReadOnly)
	TArray<FSFRoomStruct> Rooms;

	UPROPERTY(BlueprintReadWrite)
	FGameplayTag CurrentRoom;

	UFUNCTION(BlueprintCallable)
	void InitializeActorsInRoom(FGameplayTag RoomTag);

	UFUNCTION(BlueprintPure)
	bool GetRoomDataByTag(FGameplayTag RoomTag, FSFRoomStruct& RoomData) const;

	UFUNCTION(BlueprintPure)
	bool IsRoomStageCompleted(FGameplayTag RoomTag, int32 StageIndex);

	UFUNCTION(BlueprintCallable)
	bool AddActorToRoom(FGameplayTag RoomTag, FSFRoomActorStruct ActorStruct);

	UFUNCTION(BlueprintCallable)
	void RemoveActorFromRoom(FGameplayTag RoomTag, FSFRoomActorStruct ActorStruct);

	UFUNCTION(BlueprintPure)
	TSubclassOf<AActor> GetBuildActorClassByTag(FGameplayTag ActorTag) const;

	UPROPERTY(BlueprintAssignable)
	FOnRoomActorEvent OnActorAddedToRoom;

	UPROPERTY(BlueprintAssignable)
	FOnRoomActorEvent OnActorRemovedFromRoom;

	UPROPERTY(BlueprintAssignable)
	FOnRoomEvent OnRoomStageFinished;

};
