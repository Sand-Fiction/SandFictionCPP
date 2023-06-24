// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SF_InteractableComponent.h"
#include "Components/ActorComponent.h"
#include "SF_InteractionSystem.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SANDFICTIONCPP_API USF_InteractionSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USF_InteractionSystem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InteractionDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float IndicatorDistance;

	UPROPERTY()
	TArray<USF_InteractableComponent*> InteractableComponents;

	UPROPERTY(BlueprintReadOnly)
	USF_InteractableComponent* CurrentInteractable;

	UFUNCTION()
	void RegisterInteractable(USF_InteractableComponent* InteractableComponent);

	UFUNCTION()
	void UnRegisterInteractable(USF_InteractableComponent* InteractableComponent);

	UFUNCTION()
	void Interact();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void CheckInteractables();

public:
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
