// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SF_InteractionWidget.generated.h"

/**
 * 
 */
UCLASS()
class SANDFICTIONCPP_API USF_InteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	class USF_InteractableComponent* InteractableComponent;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateWidget();
	
};
