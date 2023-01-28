// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "SF_PlayerController.generated.h"

/** Forward declaration to improve compiling times */
class ASF_CameraActor_Gameplay;
class ASF_Character_Main;
class UInputAction;

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

#pragma region /** Enhanced User Input */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputMove;
	void Move(const FInputActionValue& InputActionValue);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputAttack;
	void Attack(const FInputActionValue& InputActionValue);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputInteract;
	void Interact(const FInputActionValue& InputActionValue);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputBlock;
	void Block(const FInputActionValue& InputActionValue);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputRotateCamera;
	void RotateCamera(const FInputActionValue& InputActionValue);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputJump;
	void Jump(const FInputActionValue& InputActionValue);
	void JumpEnd(const FInputActionValue& InputActionValue);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputTargetLock;
	void TargetLock(const FInputActionValue& InputActionValue);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputSkill;
	void Skill(const FInputActionValue& InputActionValue);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputZoomCamera;
	void ZoomCamera(const FInputActionValue& InputActionValue);

#pragma endregion

	// CameraRotation
	void OnRotateCameraRightPressed();
	void OnRotateCameraLeftPressed();

	// Jump
	void OnJumpPressed();
	void OnJumpReleased();
	bool JumpCheck() const;

	// Attack
	void OnAttackPressed();
	void OnAttackReleased();
	bool AttackCheck() const;

	// Skill

	void OnSkillPressed();
	void OnSkillReleased();
	bool SkillCheck() const;

	// Interact
	void OnInteractPressed();
	void OnInteractReleased();
	bool InteractCheck() const;

	bool MoveCheck() const;

	//Camera
	void SetupFollowCamera();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	ASF_CameraActor_Gameplay* FollowCamera;

};
