// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "SF_CombatComponent.generated.h"

class ASF_Skill;
// Struct for Animation DataTable
USTRUCT()
struct FCharacterAnimationData : public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* AnimMontage;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentHealthChanged, float, NewCurrentHealth);

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

	// Attack Range
	UPROPERTY(EditAnywhere, Category = Resources)
	float AttackRange = 150;

	// Maximum Health
	UPROPERTY(EditAnywhere, Category = Resources)
	float HealthMax = 100;

	// Health Regeneration per Second
	UPROPERTY(EditAnywhere, Category = Resources)
	float HealthRegen = 1;

	UFUNCTION(BlueprintCallable)
	void AttackCheck();

	UFUNCTION(BlueprintCallable)
	void MeleeAttack();

	UFUNCTION(BlueprintCallable)
	void SetCurrentHealth(float NewCurrentHealth);

	UFUNCTION(BlueprintCallable)
	void TakeDamage(USF_CombatComponent* Source);

	UFUNCTION(BlueprintCallable)
	void GetHit(USF_CombatComponent* Source);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ASF_Skill> CurrentSkillClass;

	UPROPERTY(BlueprintReadOnly)
	ASF_Skill* SpawnedSkill;

	UFUNCTION(BlueprintCallable)
	void UseSkill();

	UPROPERTY(BlueprintAssignable)
	FOnCurrentHealthChanged OnCurrentHealthChanged;

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
