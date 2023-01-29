// Copyright Epic Games, Inc. All Rights Reserved.

#include "SF_PlayerController.h"
#include "GameFramework/Pawn.h"
#include "NiagaraSystem.h"
#include "Math/Vector.h"
#include "SF_Character_Main.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "SandFictionCPP/Camera/SF_CameraActor_Gameplay.h"
#include "SandFictionCPP/Components/SF_CharacterStateComponent.h"
#include "SandFictionCPP/Components/SF_CharacterTargetComponent.h"
#include "SandFictionCPP/Components/SF_CharacterTargetSystem.h"
#include "SandFictionCPP/Components/SF_CombatComponent.h"
#include "SandFictionCPP/Components/SF_InteractionSystem.h"
#include <EnhancedInputComponent.h>
#include "EnhancedInputSubsystems.h"

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

	if (const auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Get Input Subsystem and add MappingContext
		if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(InputMapping, 0);
		}

		EnhancedInputComponent->BindAction(InputMove, ETriggerEvent::Triggered, this, &ASF_PlayerController::Move);
		EnhancedInputComponent->BindAction(InputAttack, ETriggerEvent::Triggered, this, &ASF_PlayerController::Attack);
		EnhancedInputComponent->BindAction(InputInteract, ETriggerEvent::Triggered, this, &ASF_PlayerController::Interact);
		EnhancedInputComponent->BindAction(InputInteract, ETriggerEvent::Completed, this, &ASF_PlayerController::InteractEnd);
		EnhancedInputComponent->BindAction(InputBlock, ETriggerEvent::Triggered, this, &ASF_PlayerController::Block);
		EnhancedInputComponent->BindAction(InputRotateCamera, ETriggerEvent::Triggered, this, &ASF_PlayerController::RotateCamera);
		EnhancedInputComponent->BindAction(InputJump, ETriggerEvent::Triggered, this, &ASF_PlayerController::Jump);
		EnhancedInputComponent->BindAction(InputJump, ETriggerEvent::Completed, this, &ASF_PlayerController::JumpEnd);
		EnhancedInputComponent->BindAction(InputTargetLock, ETriggerEvent::Started, this, &ASF_PlayerController::TargetLock);
		EnhancedInputComponent->BindAction(InputSkill, ETriggerEvent::Triggered, this, &ASF_PlayerController::Skill);
		EnhancedInputComponent->BindAction(InputZoomCamera, ETriggerEvent::Triggered, this, &ASF_PlayerController::ZoomCamera);
	}
}

void ASF_PlayerController::Move(const FInputActionValue& InputActionValue)
{
	if (MoveCheck())
	{
		const auto AxisInput = InputActionValue.Get<FVector2D>();
		if (AxisInput.X != 0.0f)
		{
			PawnReference->AddMovementInput(FollowCamera->GetActorForwardVector().GetSafeNormal2D(), AxisInput.X);
		}

		if (AxisInput.Y != 0.0f)
		{
			PawnReference->AddMovementInput(FollowCamera->GetActorRightVector().GetSafeNormal2D(), AxisInput.Y);
		}
	}
}

void ASF_PlayerController::Attack(const FInputActionValue& InputActionValue)
{
	if (AttackCheck())
	{
		PawnReference->GetCombatComponent()->MeleeAttack();
		StopMovement();
	}
}

void ASF_PlayerController::Interact(const FInputActionValue& InputActionValue)
{
	if (InteractCheck())
	{
		PawnReference->GetInteractionSystem()->Interact();
		PawnReference->GetCharacterStateComponent()->ChangeCharacterState(ECharacterState::Interacting);
	}
}

void ASF_PlayerController::InteractEnd(const FInputActionValue& InputActionValue)
{
	if (PawnReference && PawnReference->GetCharacterStateComponent()->CharacterState == ECharacterState::Interacting)
	{
		PawnReference->GetCharacterStateComponent()->ChangeCharacterState(ECharacterState::Idle);
	}
}

void ASF_PlayerController::Block(const FInputActionValue& InputActionValue)
{

}

void ASF_PlayerController::RotateCamera(const FInputActionValue& InputActionValue)
{
	const auto AxisInput = InputActionValue.Get<FVector2D>();
	const float Yaw = AxisInput.X + AxisInput.Y;
	const auto RotationOffset = FRotator(0, Yaw, 0);
	FollowCamera->AddActorWorldRotation(RotationOffset);
}

void ASF_PlayerController::Jump(const FInputActionValue& InputActionValue)
{
	if (JumpCheck())
	{
		PawnReference->Jump();
	}
}

void ASF_PlayerController::JumpEnd(const FInputActionValue& InputActionValue)
{
	if (PawnReference)
	{
		PawnReference->StopJumping();
	}
}

void ASF_PlayerController::TargetLock(const FInputActionValue& InputActionValue)
{
	if (PawnReference)
	{
		const auto TargetSystem = PawnReference->GetTargetSystem();
		TargetSystem->IsLockedOn ? TargetSystem->LockOff() : TargetSystem->LockOn();
	}
}

void ASF_PlayerController::Skill(const FInputActionValue& InputActionValue)
{
	if (SkillCheck())
	{
		PawnReference->GetCombatComponent()->UseSkill();
		StopMovement();
	}
}

void ASF_PlayerController::ZoomCamera(const FInputActionValue& InputActionValue)
{
	FollowCamera->ZoomCamera(InputActionValue.Get<float>());
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

bool ASF_PlayerController::AttackCheck() const
{
	if (PawnReference && !PawnReference->IsSafe)
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

bool ASF_PlayerController::SkillCheck() const
{
	if (PawnReference && !PawnReference->IsSafe)
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
		default: return false;
		}
	}	
	return false;
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

bool ASF_PlayerController::MoveCheck() const
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
