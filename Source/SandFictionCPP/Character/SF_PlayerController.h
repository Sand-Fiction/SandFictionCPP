// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SF_PlayerController.generated.h"

/** Forward declaration to improve compiling times */
class ASF_CameraActor_Gameplay;
class ASF_Character_Main;

UCLASS()
class ASF_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASF_PlayerController();

	UPROPERTY(BlueprintReadOnly, Category = References)
	ASF_Character_Main* PawnReference;

	FORCEINLINE ASF_CameraActor_Gameplay* GetFollowCamera() const { return FollowCamera; }

protected:

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Input handlers for SetDestination action. */
	void OnJumpPressed();
	void OnJumpReleased();
	bool JumpCheck() const;

	void OnAttackPressed();
	void OnAttackReleased();
	bool AttackCheck() const;

	void OnInteractPressed();
	void OnInteractReleased();
	bool InteractCheck() const;

	void OnTargetLockOnOffPressed();

	void OnMoveForward(float AxisInput);
	void OnMoveRight(float AxisInput);

	//Camera
	void SetupFollowCamera();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	ASF_CameraActor_Gameplay* FollowCamera;
};
