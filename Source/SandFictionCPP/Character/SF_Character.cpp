// Copyright Epic Games, Inc. All Rights Reserved.

#include "SF_Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "SandFictionCPP/Components/SF_CharacterFactionComponent.h"
#include "SandFictionCPP/Components/SF_CharacterStateComponent.h"
#include "SandFictionCPP/Components/SF_CharacterTargetSystem.h"

ASF_Character::ASF_Character()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Create Custom Components
	CharacterFactionComponent = CreateDefaultSubobject<USF_CharacterFactionComponent>(TEXT("FactionComponent"));
	CharacterStateComponent = CreateDefaultSubobject<USF_CharacterStateComponent>(TEXT("StateComponent"));
	TargetSystem = CreateDefaultSubobject<USF_CharacterTargetSystem>(TEXT("TargetSystem"));

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ASF_Character::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}
