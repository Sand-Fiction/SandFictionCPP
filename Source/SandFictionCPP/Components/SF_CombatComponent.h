// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "SandFictionCPP/Character/SF_CharacterEnums.h"
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

UENUM(BlueprintType)
enum ECombatStance
{
	Melee  UMETA(DisplayName = "Melee"),
	Ranged UMETA(DisplayName = "Ranged")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentHealthChanged, float, NewCurrentHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDamageTaken, float, Damage, USF_CombatComponent*, Source);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterDied);

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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Resources)
	float DamageMin;

	// Maximum Damage
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Resources)
	float DamageMax;

	// Attack Range
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Resources)
	float AttackRange;

	// Maximum Health
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Resources)
	float HealthMax;

	// Health Regeneration per Second
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Resources)
	float HealthRegen;

	UPROPERTY(BlueprintReadWrite, Category = Combat)
	int32 AttackCounter;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Combat)
	int32 MaxAttackChain;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Combat)
	TEnumAsByte<ECombatStance> CombatStance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Combat)
	UStaticMesh* MeleeWeapon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Combat)
	UStaticMesh* RangedWeapon;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Combat)
	UStaticMeshComponent* CurrentWeaponMesh;

	UFUNCTION(BlueprintCallable)
	void AttackCheck();

	UFUNCTION(BlueprintCallable)
	void MeleeAttack();

	UFUNCTION()
	void MeleeAttackEnd(ECharacterState OldCharacterState, ECharacterState NewCharacterState);

	UFUNCTION(BlueprintCallable)
	void AttachWeapon();

	UFUNCTION(BlueprintCallable)
	void DetachWeapon();

	UFUNCTION(BlueprintCallable)
	void ResetAttackCounter();

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

	UFUNCTION(BlueprintCallable)
	void StartKillOwner();

private:
	UFUNCTION()
	void EndKillOwner(UAnimMontage* AnimMontage = nullptr, bool Finished = true);

public:
	UPROPERTY(BlueprintAssignable)
	FOnCurrentHealthChanged OnCurrentHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnCharacterDied OnCharacterDied;

	UPROPERTY(BlueprintAssignable)
	FOnDamageTaken OnDamageTaken;

	// Current Health
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Resources)
	float HealthCurrent = 100;

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
