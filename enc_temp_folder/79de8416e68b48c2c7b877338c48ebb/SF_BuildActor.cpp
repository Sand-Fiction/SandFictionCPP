// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_BuildActor.h"

#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"
#include "SandFictionCPP/Character/SF_Character_Main.h"
#include "SandFictionCPP/Components/SF_BuildingComponent.h"
#include "SandFictionCPP/Components/SF_InteractableComponent.h"
#include "SandFictionCPP/Components/SF_InteractionSystem.h"

// Sets default values
ASF_BuildActor::ASF_BuildActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>("ActorMesh");
	ActorMesh->SetupAttachment(RootComponent);
	ActorMesh->SetHiddenInGame(true);

	PreviewMesh = CreateDefaultSubobject<UStaticMeshComponent>("PreviewMesh");
	PreviewMesh->SetupAttachment(RootComponent);
	PreviewMesh->SetHiddenInGame(true);

	MiniatureMesh = CreateDefaultSubobject<UStaticMeshComponent>("MiniatureMesh");
	MiniatureMesh->SetupAttachment(RootComponent);

	InteractableComponent = CreateDefaultSubobject<USF_InteractableComponent>("Interactable");
	InteractableComponent->SetupAttachment(RootComponent);

	BuildParticleSystem = CreateDefaultSubobject<UNiagaraComponent>("ParticleSystem");
	BuildParticleSystem->SetupAttachment(RootComponent);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>("AudioComponent");
	AudioComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASF_BuildActor::BeginPlay()
{
	Super::BeginPlay();

}

void ASF_BuildActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InteractableComponent->OnInteraction.AddDynamic(this, &ASF_BuildActor::OnInteract);
	PreviewMID = UMaterialInstanceDynamic::Create(PreviewMesh->GetMaterial(0), this);
	PreviewMesh->SetMaterial(0, PreviewMID);
}

void ASF_BuildActor::OnInteract(USF_InteractionSystem* Interactor)
{
	const auto OwningActor = Interactor->GetOwner();
	if (!OwningActor)
	{
		return;
	}

	const auto PlayerCharacter = Cast<ASF_Character_Main>(OwningActor);
	if (!PlayerCharacter)
	{
		return;
	}

	InteractableComponent->SetIsInteractable(false);
	SetActorEnableCollision(false);
	PreviewMesh->SetHiddenInGame(false);
	MiniatureMesh->SetHiddenInGame(false);
	ActorMesh->SetHiddenInGame(true);

	const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules
	(
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepWorld,
		false
	);
	AttachToComponent(PlayerCharacter->GetMesh(), AttachmentRules, "BuildActor");

	if (const auto BuildingComponent = PlayerCharacter->GetBuildingComponent())
	{
		BuildingComponent->SetBuildActor(this);
		BuildingComponent->StartBuildingMode();
	}
}

// Called every frame
void ASF_BuildActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASF_BuildActor::OnBuild() const
{
	InteractableComponent->SetIsInteractable(true);
	BuildParticleSystem->Activate();
	AudioComponent->SetSound(BuildSound);
	AudioComponent->Play();

	ActorMesh->SetHiddenInGame(false);
	PreviewMesh->SetHiddenInGame(true);
	MiniatureMesh->SetHiddenInGame(true);
}

void ASF_BuildActor::SetPreviewLocation(const FVector& PreviewLocation) const
{
	PreviewMesh->SetWorldLocation(PreviewLocation);
}

void ASF_BuildActor::SetPreviewMID(bool ValidLocation)
{
	FLinearColor Color;
	ValidLocation ? Color = FLinearColor::Blue : Color = FLinearColor::Red;
	PreviewMID->SetVectorParameterValue("Color", Color);
}

