// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SF_Character.h"
#include "SF_Character_Main.generated.h"

class USF_InventoryComponent;
class USF_CharacterTargetSystem;
class USF_InteractionSystem;

/**
 * 
 */
UCLASS()
class SANDFICTIONCPP_API ASF_Character_Main : public ASF_Character
{
	GENERATED_BODY()

public:

	ASF_Character_Main();

	UFUNCTION(BlueprintCallable)
	void SetCharacterSafety(bool isSafe);

	/** Returns TargetSystem SubObject **/
	FORCEINLINE USF_CharacterTargetSystem* GetTargetSystem() const { return TargetSystem; }

	/** Returns InteractionSystem SubObject **/
	FORCEINLINE USF_InteractionSystem* GetInteractionSystem() const { return InteractionSystem; }

	/** Returns InventoryComponent SubObject **/
	FORCEINLINE USF_InventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool IsSafe;

private:

	/** Target System Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	USF_CharacterTargetSystem* TargetSystem;

	/** Interaction System Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	USF_InteractionSystem* InteractionSystem;

	/** Inventory Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	USF_InventoryComponent* InventoryComponent;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float DefaultMaxWalkSpeed;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float SafeMaxWalkSpeed;

};
