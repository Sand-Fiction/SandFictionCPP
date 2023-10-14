// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SF_NPCManager.generated.h"

USTRUCT(BlueprintType)
struct FNPCWorldState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag Identifier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag World;

	FNPCWorldState()
	{

	}

	FNPCWorldState(FGameplayTag Identifier)
	{
		this->Identifier = Identifier;
	}

	FNPCWorldState(FGameplayTag Identifier, FGameplayTag World)
	{
		this->Identifier = Identifier;
		this->World = World;
	}

	bool operator== (const FGameplayTag& Other) const
	{
		return Identifier == Other;
	}

	bool operator== (const FNPCWorldState& Other) const
	{
		return Identifier == Other.Identifier;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNPCWorldStateChange, FNPCWorldState, NPCWorldState);

UCLASS(meta = (DisplayName = "NPC Manager"))
class SANDFICTIONCPP_API USF_NPCManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	UDataTable* NPCData;

	UPROPERTY()
	TArray<FNPCWorldState> NPCWorldStates;

public:

	UFUNCTION(BlueprintPure)
	TArray<FNPCWorldState> GetAllNPCWorldStages();

	UPROPERTY(BlueprintReadWrite)
	TArray<FGameplayTag> NPCs;

	UFUNCTION(BlueprintCallable)
	void Init(UDataTable* NPCDataTable);

	UFUNCTION(BlueprintPure)
	bool GetNPCWorldStageByTag(const FGameplayTag NPCTag, FNPCWorldState &WorldState) const;

	UFUNCTION(BlueprintCallable)
	void SetNPCWorld(FGameplayTag NPCTag, FGameplayTag WorldTag);

	UPROPERTY(BlueprintAssignable)
	FOnNPCWorldStateChange OnNPCWorldStateChange;
};
