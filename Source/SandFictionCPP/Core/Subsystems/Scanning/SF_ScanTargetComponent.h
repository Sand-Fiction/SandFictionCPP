// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "SF_ScanTargetComponent.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SANDFICTIONCPP_API USF_ScanTargetComponent : public UActorComponent
{
	GENERATED_BODY()

	friend class USFScanningSystem;

public:
	// Sets default values for this component's properties
	USF_ScanTargetComponent();

	UFUNCTION(BlueprintCallable)
	void Scan();

	virtual void Deactivate() override;
	virtual void Activate(bool bReset) override;

protected:

	// Once you scan one Actor of this Identity, all others can not be scanned anymore as well
	UPROPERTY(EditAnywhere)
	FGameplayTag ScanIdentity;
	
	// The resource that increments when you scan this actor
	UPROPERTY(EditAnywhere)
	FDataTableRowHandle ResourceData;

	// The overlay material that is active, if this Actor can be scanned
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> ScanOverlayMaterial;
	
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable)
	void UpdateMeshOverlayMaterial(bool bVisible);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
