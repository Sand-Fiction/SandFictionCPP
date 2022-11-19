// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "SF_InteractionWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class SANDFICTIONCPP_API USF_InteractionWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:

	USF_InteractionWidgetComponent();

	UPROPERTY(BlueprintReadOnly)
	class USF_InteractableComponent* InteractableComponent;

	UFUNCTION()
	void BindStatusChange();

private:

	UFUNCTION()
	void OnStatusChanged();
};
