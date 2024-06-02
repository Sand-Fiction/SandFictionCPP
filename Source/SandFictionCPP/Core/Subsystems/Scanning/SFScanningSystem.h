// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SF_ScanTargetComponent.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SFScanningSystem.generated.h"

/**
 * 
 */
UCLASS()
class SANDFICTIONCPP_API USFScanningSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	TArray<FGameplayTag> ScannedIdentities;

	UPROPERTY()
	TArray<USF_ScanTargetComponent*> ScanTargetArray;
	
public:

	UFUNCTION(BlueprintPure)
	FORCEINLINE TArray<FGameplayTag> GetScannedIdentities() const
	{
		return ScannedIdentities;
	}

	UFUNCTION(BlueprintCallable)
	void AddScannedIdentity(const FGameplayTag IdentityTag);

	UFUNCTION(BlueprintCallable)
	void RemoveScannedIdentity(const FGameplayTag IdentityTag);
	
	void RegisterScanTargetComponent(USF_ScanTargetComponent* ScanTarget);
	void UnRegisterScanTargetComponent(USF_ScanTargetComponent* ScanTarget);
	
};
