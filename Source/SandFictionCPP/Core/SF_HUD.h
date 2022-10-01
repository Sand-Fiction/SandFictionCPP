// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SF_HUD.generated.h"

/**
 * 
 */
UCLASS()
class SANDFICTIONCPP_API ASF_HUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
		FText CurrentDialogueLine;

	UFUNCTION(BlueprintCallable)
		void StartMainDialogue();

	UFUNCTION(BlueprintCallable)
		void SpawnSideDialogue();
	
};
