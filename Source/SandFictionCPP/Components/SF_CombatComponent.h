// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "SF_CombatComponent.generated.h"

// Struct for Animation DataTable
USTRUCT()
struct FCharacterAnimationData : public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* AnimMontage;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SANDFICTIONCPP_API USF_CombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USF_CombatComponent();

	UPROPERTY(EditAnywhere, Category = Animation)
	UDataTable* AnimDataTable;

	// Minimum Damage
	UPROPERTY(EditAnywhere, Category = Resources)
	float DamageMin = 5;

	// Maximum Damage
	UPROPERTY(EditAnywhere, Category = Resources)
	float DamageMax = 15;

	// Maximum Health
	UPROPERTY(EditAnywhere, Category = Resources)
	float HealthMax = 100;

	// Health Regeneration per Second
	UPROPERTY(EditAnywhere, Category = Resources)
	float HealthRegen = 1;


	UFUNCTION()
	void MeleeAttack();

	UFUNCTION()
	void GetHit(USF_CombatComponent* Source);

private:

	// Current Health
	UPROPERTY(VisibleAnywhere, Category = Resources)
	float HealthCurrent = 100;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
