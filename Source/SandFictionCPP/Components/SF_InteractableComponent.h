// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SF_InteractableComponent.generated.h"

class USF_InteractionSystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteraction, USF_InteractionSystem*, Interactor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStatusChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SANDFICTIONCPP_API USF_InteractableComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USF_InteractableComponent();

	/** Gets this Components Active Status **/
	FORCEINLINE bool GetIsActive() const { return Active; }
	/** Gets this Components Active Status **/
	FORCEINLINE bool GetIsInRange() const { return InRange; }

	UFUNCTION()
	void SetInRange(bool isInRange);

	UFUNCTION()
	void SetIsActive(bool isActive);

	UPROPERTY(BlueprintAssignable)
	FOnInteraction OnInteraction;

	UPROPERTY(BlueprintAssignable)
	FOnStatusChanged OnStatusChanged;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class USF_InteractionWidgetComponent* InteractWidgetComponent;

protected:

	UPROPERTY(BlueprintReadOnly)
	bool InRange = false;

	UPROPERTY(BlueprintReadOnly)
	bool Active = false;

	void RegisterInteractable();
	void UnRegisterInteractable();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called when the Component get's destroyed
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
		
};
