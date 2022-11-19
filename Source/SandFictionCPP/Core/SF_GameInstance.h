// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SF_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SANDFICTIONCPP_API USF_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	TSubclassOf<UUserWidget> InteractionWidgetClass;
};