// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "SF_BuildingComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBuildModeEvent);
class ASF_BuildActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SANDFICTIONCPP_API USF_BuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USF_BuildingComponent();

	UFUNCTION(BlueprintCallable)
	void ToggleBuildingMode();

	UFUNCTION(BlueprintCallable)
	void StartBuildingMode();

	UFUNCTION(BlueprintCallable)
	void EndBuildingMode();

	UFUNCTION(BlueprintPure)
	bool IsInBuildingMode() const;

	UFUNCTION(BlueprintCallable)
	void SetBuildActor(ASF_BuildActor* Actor);

	UFUNCTION(BlueprintCallable)
	void BuildActor();

	UPROPERTY(BlueprintAssignable)
	FBuildModeEvent OnBuildModeStart;

	UPROPERTY(BlueprintAssignable)
	FBuildModeEvent OnBuildModeEnd;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool FindBuildLocation(FVector& BuildLocation, FGameplayTag& InsideRoom) const;

	UPROPERTY(VisibleAnywhere)
	bool bBuildingModeEnabled;

	UPROPERTY(EditDefaultsOnly)
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* PickUpAnimMontage;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* BuildAnimMontage;

	UPROPERTY()
	ASF_BuildActor* CurrentBuildActor;

	UFUNCTION()
	void OnBuildAnimFinished();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
