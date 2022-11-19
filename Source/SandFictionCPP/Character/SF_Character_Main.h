// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SF_Character.h"
#include "SF_Character_Main.generated.h"

/**
 * 
 */
UCLASS()
class SANDFICTIONCPP_API ASF_Character_Main : public ASF_Character
{
	GENERATED_BODY()

public:

	ASF_Character_Main();

	/** Returns TargetSystem SubObject **/
	FORCEINLINE class USF_CharacterTargetSystem* GetTargetSystem() const { return TargetSystem; }

	/** Returns InteractionSystem SubObject **/
	FORCEINLINE class USF_InteractionSystem* GetInteractionSystem() const { return InteractionSystem; }

private:

	/** Target System Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	class USF_CharacterTargetSystem* TargetSystem;

	/** Interaction System Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	class USF_InteractionSystem* InteractionSystem;

};
