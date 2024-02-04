// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "SF_CharacterEnums.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Idle,
	Running,
	Falling,
	Attacking,
	GettingHit,
	Blocking,
	Rolling,
	Interacting,
	Dying
};

UENUM(BlueprintType)
enum class ECharacterFaction : uint8
{
	Player,
	Neutral,
	Enemy
};