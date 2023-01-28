// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SF_Character.h"
#include "SF_Character_Enemy.generated.h"

UCLASS()
class SANDFICTIONCPP_API ASF_Character_Enemy : public ASF_Character
{
	GENERATED_BODY()

public:

	ASF_Character_Enemy();

	/** Returns FactionComponent SubObject **/
	FORCEINLINE class UFlowComponent* GetFlowComponent() const { return FlowComponent; }

	/** Returns FactionComponent SubObject **/
	FORCEINLINE class USF_CharacterTargetComponent* GetTargetComponent() const { return TargetComponent; }

private:

	/** Flow Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	UFlowComponent* FlowComponent;

	/** Target Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	USF_CharacterTargetComponent* TargetComponent;

protected:

	virtual void StartDeath() override;
	
};
