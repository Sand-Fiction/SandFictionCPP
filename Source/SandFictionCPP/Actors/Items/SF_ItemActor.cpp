// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_ItemActor.h"

#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Components/AudioComponent.h"
#include "SandFictionCPP/Character/SF_Character_Main.h"
#include "SandFictionCPP/Components/SF_InteractableComponent.h"

// Sets default values
ASF_ItemActor::ASF_ItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMeshComponent->SetupAttachment(RootComponent);

	InteractableComponent = CreateDefaultSubobject<USF_InteractableComponent>("Interactable");
	InteractableComponent->SetupAttachment(RootComponent);

	ParticleSystem = CreateDefaultSubobject<UNiagaraComponent>("ParticleSystem");
	ParticleSystem->SetupAttachment(RootComponent);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>("AudioComponent");
	AudioComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASF_ItemActor::BeginPlay()
{
	Super::BeginPlay();

	AudioComponent->SetSound(IdleSound);
	AudioComponent->Play();
}

void ASF_ItemActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InteractableComponent->OnInteraction.AddDynamic(this, &ASF_ItemActor::OnInteract);
}

void ASF_ItemActor::OnInteract(USF_InteractionSystem* Interactor)
{
	const auto OwningActor = Interactor->GetOwner();
	const auto PlayerCharacter = Cast<ASF_Character_Main>(OwningActor);

	if (!PlayerCharacter)
	{
		return;
	}

	PlayerCharacter->GetInventoryComponent()->AddItemToInventory(ItemData);

	AudioComponent->SetSound(PickUpSound);
	AudioComponent->Play();

	AudioComponent->OnAudioFinished.AddDynamic(this, &ASF_ItemActor::OnAudioFinished);
	StaticMeshComponent->DestroyComponent();
	InteractableComponent->DestroyComponent();
	ParticleSystem->DestroyComponent();
}

void ASF_ItemActor::OnAudioFinished()
{
	Destroy();
}

// Called every frame
void ASF_ItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

