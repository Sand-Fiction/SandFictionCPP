// Copyright Epic Games, Inc. All Rights Reserved.

#include "SF_Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "SandFictionCPP/Components/SF_CharacterFactionComponent.h"
#include "SandFictionCPP/Components/SF_CharacterStateComponent.h"
#include "SandFictionCPP/Components/SF_CombatComponent.h"

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
	CombatComponent = CreateDefaultSubobject<USF_CombatComponent>(TEXT("CombatComponent"));

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
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

void ASF_Character::SetIsCharging(bool IsCharging)
{
	bIsCharging = IsCharging;
}

bool ASF_Character::GetIsCharging()
{
	return bIsCharging;
}

void ASF_Character::StartDeath()
{
	ReceiveStartDeath();
}

void ASF_Character::BeginPlay()
{
	Super::BeginPlay();

	CombatComponent->OnCharacterDied.AddUniqueDynamic(this, &ASF_Character::StartDeath);

}

void ASF_Character::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);

	// Go back to Idle if Previous Mode was Falling
	if (PrevMovementMode == EMovementMode::MOVE_Falling)
	{
		GetCharacterStateComponent()->ChangeCharacterState(ECharacterState::Idle);
	}

	// Set State to Falling if MovementMode is Falling
	if (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Falling)
	{
		GetCharacterStateComponent()->ChangeCharacterState(ECharacterState::Falling);
	}
}
