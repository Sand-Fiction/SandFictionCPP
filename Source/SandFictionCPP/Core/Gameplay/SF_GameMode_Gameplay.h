// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SandFictionCPP/Core/SF_GameMode.h"
#include "SF_GameMode_Gameplay.generated.h"

UCLASS()
class SANDFICTIONCPP_API ASF_GameMode_Gameplay : public ASF_GameMode
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SpawnAllNPCs();
};
