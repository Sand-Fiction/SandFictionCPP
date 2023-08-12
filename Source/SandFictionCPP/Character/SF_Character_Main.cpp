// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_Character_Main.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "SandFictionCPP/Components/SF_BuildingComponent.h"
#include "SandFictionCPP/Components/SF_CharacterTargetSystem.h"
#include "SandFictionCPP/Components/SF_InteractionSystem.h"
#include "SandFictionCPP/Components/SF_InventoryComponent.h"
#include "SandFictionCPP/Components/SF_RecipeBookComponent.h"


ASF_Character_Main::ASF_Character_Main()
{
	TargetSystem = CreateDefaultSubobject<USF_CharacterTargetSystem>(TEXT("TargetSystem"));
	InteractionSystem = CreateDefaultSubobject<USF_InteractionSystem>(TEXT("InteractionSystem"));
	InventoryComponent = CreateDefaultSubobject<USF_InventoryComponent>(TEXT("InventoryComponent"));
	BuildingComponent = CreateDefaultSubobject<USF_BuildingComponent>(TEXT("BuildingComponent"));
	RecipeBookComponent = CreateDefaultSubobject<USF_RecipeBookComponent>(TEXT("RecipeBookComponent"));

	IsSafe = false;
	DefaultMaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	SafeMaxWalkSpeed = DefaultMaxWalkSpeed / 1.5f;
}

void ASF_Character_Main::SetCharacterSafety(bool isSafe)
{
	IsSafe = isSafe;
	GetCharacterMovement()->MaxWalkSpeed = IsSafe ? SafeMaxWalkSpeed : DefaultMaxWalkSpeed;
}