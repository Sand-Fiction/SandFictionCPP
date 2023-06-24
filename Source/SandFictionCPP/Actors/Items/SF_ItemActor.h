// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SandFictionCPP/Components/SF_InteractionSystem.h"
#include "SandFictionCPP/Components/SF_InventoryComponent.h"
#include "SF_ItemActor.generated.h"

class UNiagaraComponent;
class USF_InteractableComponent;

UCLASS()
class SANDFICTIONCPP_API ASF_ItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASF_ItemActor();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	USF_InteractableComponent* InteractableComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* AudioComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* ParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SF | Item", meta = (AllowPrivateAccess = "true"))
	FInventoryData ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SF | Item", meta = (AllowPrivateAccess = "true"))
	USoundBase* IdleSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SF | Item", meta = (AllowPrivateAccess = "true"))
	USoundBase* PickUpSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnInteract(USF_InteractionSystem* Interactor);

	UFUNCTION()
	void OnAudioFinished();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
