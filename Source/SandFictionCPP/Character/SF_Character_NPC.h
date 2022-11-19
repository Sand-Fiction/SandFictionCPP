// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SF_Character.h"
#include "SF_Character_NPC.generated.h"

UCLASS()
class SANDFICTIONCPP_API ASF_Character_NPC : public ASF_Character
{
	GENERATED_BODY()

public:

	ASF_Character_NPC();

	/** Returns FactionComponent SubObject **/
	FORCEINLINE class USF_InteractableComponent* GetInteractableComponent() const { return InteractableComponent; }

	/** Returns FactionComponent SubObject **/
	FORCEINLINE class UFlowComponent* GetFlowComponent() const { return FlowComponent; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag Dialogue;

private:

	/** Interactable Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	USF_InteractableComponent* InteractableComponent;

	/** Flow Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	UFlowComponent* FlowComponent;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartDialogue();
};
