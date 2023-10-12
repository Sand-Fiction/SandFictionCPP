// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "SandFictionCPP/Components/SF_InteractionSystem.h"
#include "SF_BuildActor.generated.h"

class UNiagaraComponent;
class USF_InteractableComponent;

UCLASS()
class SANDFICTIONCPP_API ASF_BuildActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASF_BuildActor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	FGameplayTag Identifier;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Gameplay)
	FGameplayTag Room;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ActorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PreviewMesh;

	UPROPERTY()
	UMaterialInstanceDynamic* PreviewMID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MiniatureMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	USF_InteractableComponent* InteractableComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* AudioComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* BuildParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SF | Item", meta = (AllowPrivateAccess = "true"))
	USoundBase* BuildSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnInteract(USF_InteractionSystem* Interactor);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnBuild() const;

	void SetPreviewLocation(const FVector& PreviewLocation) const;
	void SetPreviewMID(bool ValidLocation);
};
