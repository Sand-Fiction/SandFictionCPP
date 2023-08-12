// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SF_GameMode.generated.h"

UCLASS(minimalapi)
class ASF_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASF_GameMode();

	UFUNCTION(BlueprintCallable)
	void TravelToMap(FString MapString);

	UFUNCTION(BlueprintCallable)
	void ReturnToSpaceship();

protected:
	void StartLoadingScreenFadeDelay();

	UPROPERTY()
	FString NextLevelName;

	UFUNCTION()
	void OpenLevelAfterLoadingScreenFade();

	virtual void GenericPlayerInitialization(AController* C) override;

	virtual void PostSeamlessTravel() override;

};



