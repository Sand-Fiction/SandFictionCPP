// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SF_ConditionManager.generated.h"

/**
 * 
 */
UCLASS()
class SANDFICTIONCPP_API USF_ConditionManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FGameplayTag> GameplayConditions;

public:

	UFUNCTION(BlueprintPure)
	bool HasCondition(const FGameplayTag ConditionTag) const;

	UFUNCTION(BlueprintCallable)
	void AddCondition(const FGameplayTag ConditionTag);

	UFUNCTION(BlueprintCallable)
	void RemoveCondition(const FGameplayTag ConditionTag);
	

};
