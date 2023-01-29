// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SF_CameraActor_Gameplay.generated.h"

class USF_CameraTransition;
class USpringArmComponent;
class UCameraComponent;

UENUM()
enum EZoomState
{
	None	UMETA(DisplayName = "NoZoom"),
	Zoom	UMETA(DisplayName = "Zooming"),
};

UCLASS()
class SANDFICTIONCPP_API ASF_CameraActor_Gameplay : public AActor
{
	GENERATED_BODY()

public:
	/** Returns CameraComponent subobject **/
	FORCEINLINE UCameraComponent* GetTopDownCameraComponent() const { return CameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return SpringArmComponent; }

	UPROPERTY(EditAnywhere)
	float CameraForwardOffset = 50.0f;

	UPROPERTY(EditAnywhere)
	float CameraInterpolationSpeed = 8.0f;

	UPROPERTY(EditAnywhere)
	float CameraZoomStep = 100.0f;

	UPROPERTY(EditAnywhere)
	float CameraZoomSpeed = 5.0f;

	UFUNCTION(BlueprintCallable)
	void SwitchCameraTarget(AActor* NewTarget, TSubclassOf<USF_CameraTransition> Transition);

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float MinSpringArmLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float MaxSpringArmLength;

	UFUNCTION()
	void ZoomCamera(float Input);

private:	
	// Sets default values for this actor's properties
	ASF_CameraActor_Gameplay();

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	AActor* CurrentCameraTarget;

	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float CurrentCameraZoom;

	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float CameraZoomMin;

	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float CameraZoomMax;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float CurrentSpringArmLength;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float SpringArmZoomTarget;

	UPROPERTY()
	TEnumAsByte<EZoomState> ZoomState;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
