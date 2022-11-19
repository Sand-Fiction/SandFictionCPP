// Copyright Epic Games, Inc. All Rights Reserved.

#include "SF_PlayerController.h"
#include "GameFramework/Pawn.h"
#include "NiagaraSystem.h"
#include "Math/Vector.h"
#include "SF_Character_Main.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "SandFictionCPP/Camera/SF_CameraActor_Gameplay.h"
#include "SandFictionCPP/Components/SF_CharacterStateComponent.h"
#include "SandFictionCPP/Components/SF_CharacterTargetComponent.h"
#include "SandFictionCPP/Components/SF_CharacterTargetSystem.h"
#include "SandFictionCPP/Components/SF_CombatComponent.h"
#include "SandFictionCPP/Components/SF_InteractionSystem.h"

ASF_PlayerController::ASF_PlayerController()
{
	
}

// Initialization
void ASF_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	PawnReference = Cast<ASF_Character_Main>(GetCharacter());
	SetupFollowCamera();
}

//Tick -> Move Pawn to Cursor Location if RMB Input
void ASF_PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (!PawnReference)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("PawnNotValid"));
	}

	if (PawnReference && PawnReference->GetTargetSystem())
	{
		if (PawnReference->GetTargetSystem()->IsLockedOn)
		{
			PawnReference->bUseControllerRotationYaw = true;

			FRotator NewControlRotation;
			const auto LookAtStart = PawnReference->GetActorLocation();
			const auto LookAtEnd = PawnReference->GetTargetSystem()->CurrentTarget->GetComponentLocation();
			const auto LookAtRotation = UKismetMathLibrary::FindLookAtRotation(LookAtStart, LookAtEnd);

			NewControlRotation.Roll = ControlRotation.Roll;
			NewControlRotation.Pitch = ControlRotation.Pitch;
			NewControlRotation.Yaw = LookAtRotation.Yaw;

			SetControlRotation(NewControlRotation);
		}
		else
		{
			PawnReference->bUseControllerRotationYaw = false;
		}
	}
}

void ASF_PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("Jump", IE_Pressed, this, &ASF_PlayerController::OnJumpPressed);
	InputComponent->BindAction("Jump", IE_Released, this, &ASF_PlayerController::OnJumpReleased);

	InputComponent->BindAction("Attack", IE_Pressed, this, &ASF_PlayerController::OnAttackPressed);
	InputComponent->BindAction("Attack", IE_Released, this, &ASF_PlayerController::OnAttackReleased);

	InputComponent->BindAction("Interact", IE_Pressed, this, &ASF_PlayerController::OnInteractPressed);
	InputComponent->BindAction("Interact", IE_Released, this, &ASF_PlayerController::OnInteractReleased);

	InputComponent->BindAction("TargetLockOnOff", IE_Pressed, this, &ASF_PlayerController::OnTargetLockOnOffPressed);

	InputComponent->BindAxis("MoveForward", this, &ASF_PlayerController::OnMoveForward);
	InputComponent->BindAxis("MoveRight", this, &ASF_PlayerController::OnMoveRight);
}

bool ASF_PlayerController::JumpCheck() const
{
	if (PawnReference)
	{
		switch (PawnReference->GetCharacterStateComponent()->CharacterState)
		{
		case ECharacterState::Idle: return true;
		case ECharacterState::Running: return true;
		case ECharacterState::Falling: return false;
		case ECharacterState::Attacking: return false;
		case ECharacterState::GettingHit: return false;
		case ECharacterState::Blocking: return true;
		case ECharacterState::Rolling: return false;
		case ECharacterState::Interacting: return false;
		default: return true;
		}
	}
	return false;
}

void ASF_PlayerController::OnJumpPressed()
{
	if (PawnReference)
	{
		if (JumpCheck())
		{
			PawnReference->Jump();
		}
	}
}

void ASF_PlayerController::OnJumpReleased()
{
	if (PawnReference != nullptr)
	{
		PawnReference->StopJumping();
	}
}

bool ASF_PlayerController::AttackCheck() const
{
	if (PawnReference)
	{
		switch (PawnReference->GetCharacterStateComponent()->CharacterState)
		{
		case ECharacterState::Idle: return true;
		case ECharacterState::Running: return true;
		case ECharacterState::Falling: return false;
		case ECharacterState::Attacking: return false;
		case ECharacterState::GettingHit: return false;
		case ECharacterState::Blocking: return true;
		case ECharacterState::Rolling: return false;
		case ECharacterState::Interacting: return false;
		default: return true;
		}
	}
	return false;
}

void ASF_PlayerController::OnAttackPressed()
{
	if (PawnReference)
	{
		if (AttackCheck())
		{
			PawnReference->GetCombatComponent()->MeleeAttack();
		}
	}
	
	StopMovement();
}

void ASF_PlayerController::OnAttackReleased()
{

}

bool ASF_PlayerController::InteractCheck() const
{
	if (PawnReference)
	{
		switch (PawnReference->GetCharacterStateComponent()->CharacterState)
		{
		case ECharacterState::Idle: return true;
		case ECharacterState::Running: return true;
		case ECharacterState::Falling: return false;
		case ECharacterState::Attacking: return false;
		case ECharacterState::GettingHit: return false;
		case ECharacterState::Blocking: return true;
		case ECharacterState::Rolling: return false;
		case ECharacterState::Interacting: return true;
		default: return true;
		}
	}
	return false;
}

void ASF_PlayerController::OnInteractPressed()
{
	if (PawnReference && InteractCheck())
	{
		PawnReference->GetInteractionSystem()->Interact();
		PawnReference->GetCharacterStateComponent()->ChangeCharacterState(ECharacterState::Interacting);
	}
}

void ASF_PlayerController::OnInteractReleased()
{
	if (PawnReference && PawnReference->GetCharacterStateComponent()->CharacterState == ECharacterState::Interacting)
	{
		PawnReference->GetCharacterStateComponent()->ChangeCharacterState(ECharacterState::Idle);
	}
}

void ASF_PlayerController::OnTargetLockOnOffPressed()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Target"));

	if (PawnReference)
	{
		const auto TargetSystem = PawnReference->GetTargetSystem();
		TargetSystem->IsLockedOn ? TargetSystem->LockOff() : TargetSystem->LockOn();
	}
}

void ASF_PlayerController::OnMoveForward(float AxisInput)
{
	if (PawnReference)
	{
		PawnReference->AddMovementInput(FollowCamera->GetActorForwardVector(), AxisInput);
	}
}

void ASF_PlayerController::OnMoveRight(float AxisInput)
{
	if (PawnReference)
	{
		PawnReference->AddMovementInput(FollowCamera->GetActorRightVector(), AxisInput);
	}
}

// Spawn Follow Camera at Pawns Location or 0/0/0
void ASF_PlayerController::SetupFollowCamera()
{
	FVector Location;
	if (PawnReference)
	{
		Location = PawnReference->GetActorLocation();
	}
	else
	{
		Location = FVector::ZeroVector;
	}
	const auto SpawnedActor = GetWorld()->SpawnActor(ASF_CameraActor_Gameplay::StaticClass(), &Location);
	FollowCamera = Cast<ASF_CameraActor_Gameplay>(SpawnedActor);
	SetViewTarget(FollowCamera);
}
