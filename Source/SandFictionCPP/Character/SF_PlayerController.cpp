// Copyright Epic Games, Inc. All Rights Reserved.

#include "SF_PlayerController.h"
#include "GameFramework/Pawn.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "SF_Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "SandFictionCPP/Camera/SF_CameraActor_Gameplay.h"
#include "SandFictionCPP/Components/SF_CharacterStateComponent.h"
#include "SandFictionCPP/Components/SF_CharacterTargetSystem.h"

ASF_PlayerController::ASF_PlayerController()
{
	
}

// Initialization
void ASF_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	PawnReference = Cast<ASF_Character>(GetCharacter());

	SetupFollowCamera();

}

//Tick -> Move Pawn to Cursor Location if RMB Input
void ASF_PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (PawnReference == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("PawnNotValid"));
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
	if (PawnReference != nullptr)
	{
		switch (PawnReference->GetCharacterStateComponent()->CharacterState)
		{
		case ECharacterState::Idle: return true;
		case ECharacterState::Running: return true;
		case ECharacterState::Falling: return false;
		case ECharacterState::Attacking: return false;
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
	
	if (PawnReference != nullptr)
	{
		if (JumpCheck())
		{
			PawnReference->Jump();
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Jump"));
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

void ASF_PlayerController::OnAttackPressed()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Attack"));
	StopMovement();
}

void ASF_PlayerController::OnAttackReleased()
{

}

void ASF_PlayerController::OnInteractPressed()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Interact"));
}

void ASF_PlayerController::OnInteractReleased()
{

}

void ASF_PlayerController::OnTargetLockOnOffPressed()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Target"));

	if (const auto TargetSystem = PawnReference->GetTargetSystem())
	{
		TargetSystem->IsLockedOn ? TargetSystem->LockOff() : TargetSystem->LockOn();
	}
}

void ASF_PlayerController::OnMoveForward(float AxisInput)
{
	if (PawnReference != nullptr)
	{
		/*
		const auto SpringArm = PawnReference->GetCameraBoom();
		const auto Rotation = SpringArm->GetTargetRotation();
		const FRotator Rotation2D(0, Rotation.Yaw, 0);
		const auto WorldDirection = UKismetMathLibrary::GetForwardVector(Rotation2D);
		PawnReference->AddMovementInput(WorldDirection, AxisInput);
		*/
		PawnReference->AddMovementInput(FollowCamera->GetActorForwardVector(), AxisInput);
	}
}

void ASF_PlayerController::OnMoveRight(float AxisInput)
{
	if (PawnReference != nullptr)
	{
		/*
		const auto SpringArm = PawnReference->GetCameraBoom();
		const auto Rotation = SpringArm->GetTargetRotation();
		const FRotator Rotation2D(0,Rotation.Yaw,0);
		const auto WorldDirection = UKismetMathLibrary::GetRightVector(Rotation2D);
		PawnReference->AddMovementInput(WorldDirection, AxisInput);
		*/

		PawnReference->AddMovementInput(FollowCamera->GetActorRightVector(), AxisInput);
	}
}

// Spawn Follow Camera at Pawns Location or 0/0/0
void ASF_PlayerController::SetupFollowCamera()
{
	FVector Location;
	if (PawnReference != nullptr)
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
