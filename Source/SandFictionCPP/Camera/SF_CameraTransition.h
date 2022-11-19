// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SF_CameraTransition.generated.h"

/**
 * 
 */
UCLASS()
class SANDFICTIONCPP_API USF_CameraTransition : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	bool Instant;

	UPROPERTY(meta = (EditCondition = "Instant"))
	float Duration;
};
