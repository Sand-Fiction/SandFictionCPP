// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SF_Skill.generated.h"

class USF_CombatComponent;

UCLASS( BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SANDFICTIONCPP_API ASF_Skill : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ASF_Skill();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SkillDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SkillCooldown;

	UPROPERTY(BlueprintReadOnly)
	USF_CombatComponent* CombatComponent;

	UFUNCTION(BlueprintNativeEvent)
	void SkillStart();

	UFUNCTION(BlueprintCallable)
	void SkillEnd();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

		
};
