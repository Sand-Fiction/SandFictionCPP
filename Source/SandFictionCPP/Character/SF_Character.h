// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SF_Character.generated.h"

UCLASS(Blueprintable)
class ASF_Character : public ACharacter
{
	GENERATED_BODY()

public:
	ASF_Character();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns CameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return CameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FactionComponent subobject **/
	FORCEINLINE class USF_CharacterFactionComponent* GetFactionComponent() const { return CharacterFactionComponent; }
	/** Returns StateComponent subobject **/
	FORCEINLINE class USF_CharacterStateComponent* GetCharacterStateComponent() const { return CharacterStateComponent; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Faction Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	class USF_CharacterFactionComponent* CharacterFactionComponent;

	/** State Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	class USF_CharacterStateComponent* CharacterStateComponent;
};

