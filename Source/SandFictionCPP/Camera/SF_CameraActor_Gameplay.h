// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SF_CameraActor_Gameplay.generated.h"

class USF_CameraTransition;

UCLASS()
class SANDFICTIONCPP_API ASF_CameraActor_Gameplay : public AActor
{
	GENERATED_BODY()

public:
	/** Returns CameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return CameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return SpringArmComponent; }

	UPROPERTY(EditAnywhere)
	float CameraForwardOffset = 50;

	UPROPERTY(EditAnywhere)
	float CameraInterpolationSpeed = 8;

	UFUNCTION(BlueprintCallable)
	void SwitchCameraTarget(AActor* NewTarget, TSubclassOf<USF_CameraTransition> Transition);

private:	
	// Sets default values for this actor's properties
	ASF_CameraActor_Gameplay();

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	AActor* CurrentCameraTarget;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
