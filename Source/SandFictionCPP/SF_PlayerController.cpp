// Copyright Epic Games, Inc. All Rights Reserved.

#include "SF_PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "SF_Character.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"

ASF_PlayerController::ASF_PlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

// Initialization
void ASF_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	PawnReference = GetCharacter();
}

//Tick -> Move Pawn to Cursor Location if RMB Input
void ASF_PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (PawnReference == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("PawnNotValid"));
	}

	if (bInputPressed)
	{
		FollowTime += DeltaTime;

		// Look for Cursor location
		FVector HitLocation = FVector::ZeroVector;
		FHitResult Hit;
		
		{
			GetHitResultUnderCursor(ECC_Visibility, true, Hit);
		}
		HitLocation = Hit.Location;

		// Direct the Pawn towards that location
		if(PawnReference)
		{
			const FVector WorldDirection = (HitLocation - PawnReference->GetActorLocation()).GetSafeNormal();
			PawnReference->AddMovementInput(WorldDirection, 1.f, false);
		}
	}
	else
	{
		FollowTime = 0.f;
	}
}

void ASF_PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ASF_PlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ASF_PlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ASF_PlayerController::OnJumpPressed);
	InputComponent->BindAction("Jump", IE_Released, this, &ASF_PlayerController::OnJumpReleased);

	InputComponent->BindAction("Attack", IE_Pressed, this, &ASF_PlayerController::OnAttackPressed);
	InputComponent->BindAction("Attack", IE_Released, this, &ASF_PlayerController::OnAttackReleased);

	InputComponent->BindAction("Interact", IE_Pressed, this, &ASF_PlayerController::OnInteractPressed);
	InputComponent->BindAction("Interact", IE_Released, this, &ASF_PlayerController::OnInteractReleased);
}

void ASF_PlayerController::OnSetDestinationPressed()
{
	// We flag that the input is being pressed
	bInputPressed = true;
	// Just in case the character was moving because of a previous short press we stop it
	StopMovement();
}

void ASF_PlayerController::OnSetDestinationReleased()
{
	// Player is no longer pressing the input
	bInputPressed = false;

	// If it was a short press
	if(FollowTime <= ShortPressThreshold)
	{
		// We look for the location in the world where the player has pressed the input
		FVector HitLocation = FVector::ZeroVector;
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, true, Hit);
		HitLocation = Hit.Location;

		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, HitLocation);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, HitLocation, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}
}

bool ASF_PlayerController::JumpCheck()
{
	if (PawnReference->GetMovementComponent()->IsFalling())
	{
		return false;
	}

	else
	{
		return true;
	}	
}

void ASF_PlayerController::OnJumpPressed()
{
	
	if (JumpCheck())
	{
		PawnReference->Jump();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Jump"));
	}
}

void ASF_PlayerController::OnJumpReleased()
{
	PawnReference->StopJumping();
}

void ASF_PlayerController::OnAttackPressed()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Attack"));
	StopMovement();
}

void ASF_PlayerController::OnAttackReleased()
{
}

void ASF_PlayerController::OnInteractPressed()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Interact"));
}

void ASF_PlayerController::OnInteractReleased()
{
}
