// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_CameraActor_Gameplay.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SandFictionCPP/Camera/SF_CameraTransition.h"


// Sets default values
ASF_CameraActor_Gameplay::ASF_CameraActor_Gameplay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Root
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// Create a SpringArm...
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetUsingAbsoluteRotation(false); // Don't want arm to rotate when character does
	SpringArmComponent->TargetArmLength = 800;
	SpringArmComponent->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArmComponent->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->bEnableCameraRotationLag = true;
	SpringArmComponent->CameraLagSpeed = 12;
	SpringArmComponent->CameraRotationLagSpeed = 5;

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

// Called when the game starts or when spawned
void ASF_CameraActor_Gameplay::BeginPlay()
{
	Super::BeginPlay();
	CurrentCameraTarget = UGameplayStatics::GetPlayerCharacter(this, 0);
}

// Called every frame
void ASF_CameraActor_Gameplay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Interpolate to offsetted Location in front of CurrentCameraTarget
	const auto NewCamLocation = (CurrentCameraTarget->GetActorLocation()) + (CurrentCameraTarget->GetActorForwardVector() * CameraForwardOffset);
	const auto NewCamLocationInterp = FMath::VInterpTo(GetActorLocation(), NewCamLocation, DeltaTime, CameraInterpolationSpeed);
	SetActorLocation(NewCamLocationInterp);
}

void ASF_CameraActor_Gameplay::SwitchCameraTarget(AActor* NewTarget, TSubclassOf<USF_CameraTransition> Transition)
{
	CurrentCameraTarget = NewTarget;
}
