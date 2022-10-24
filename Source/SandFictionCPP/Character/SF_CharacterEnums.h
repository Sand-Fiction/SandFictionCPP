// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "SF_CharacterEnums.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Running,
	Attacking,
	Blocking,
	Rolling,
	Interacting
};