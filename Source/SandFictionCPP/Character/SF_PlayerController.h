// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SF_Character.h"
#include "GameFramework/PlayerController.h"
#include "SF_PlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;

UCLASS()
class ASF_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASF_PlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	UPROPERTY(BlueprintReadOnly, Category = References)
	ASF_Character* PawnReference;	

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	bool JumpCheck() const;
	void OnJumpPressed();
	void OnJumpReleased();

	void OnAttackPressed();
	void OnAttackReleased();

	void OnInteractPressed();
	void OnInteractReleased();

	void OnTargetLockOnOffPressed();

	void OnMoveForward(float AxisInput);
	void OnMoveRight(float AxisInput);

	// Rotation Function
	void RotateToCursor(FVector HitLocation);
	

private:
	bool bInputPressed; // Input is bring pressed
	float FollowTime; // For how long it has been pressed
};
