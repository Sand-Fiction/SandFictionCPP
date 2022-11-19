// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SandFictionCPP/Components/SF_CharacterTargetSystem.h"
#include "SF_CharacterTargetComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SANDFICTIONCPP_API USF_CharacterTargetComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USF_CharacterTargetComponent();

protected:
	// Called when the game starts

	UPROPERTY(BlueprintReadOnly)
	USF_CharacterTargetSystem* TargetSystem = nullptr;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
		
};
