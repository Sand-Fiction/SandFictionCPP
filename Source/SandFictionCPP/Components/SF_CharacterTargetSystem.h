// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SF_CharacterTargetSystem.generated.h"

class USF_CharacterTargetComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SANDFICTIONCPP_API USF_CharacterTargetSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USF_CharacterTargetSystem();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(BlueprintReadOnly)
	class UWidgetComponent* WidgetComponent;

	UPROPERTY(BlueprintReadWrite)
	TArray<USF_CharacterTargetComponent*> TargetComponents;

	UFUNCTION(BlueprintCallable)
	void RegisterTargetComponent(USF_CharacterTargetComponent* TargetComponent);

	UFUNCTION(BlueprintCallable)
	void UnRegisterTargetComponent(USF_CharacterTargetComponent* TargetComponent);

	UFUNCTION(BlueprintCallable)
	void LockOn();

	UFUNCTION(BlueprintCallable)
	void LockOff();

	UPROPERTY(EditAnywhere)
	float MaxLockOnDistance = 1000;

	UPROPERTY(BlueprintReadOnly)
	bool IsLockedOn;

	UPROPERTY(BlueprintReadOnly)
	USF_CharacterTargetComponent* CurrentTarget;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SpawnWidgetComponent();
	void DestroyWidgetComponent();

};
