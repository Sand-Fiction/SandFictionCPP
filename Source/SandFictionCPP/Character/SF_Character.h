// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SF_Character.generated.h"

UCLASS(Blueprintable)
class ASF_Character : public ACharacter
{
	GENERATED_BODY()

public:
	ASF_Character();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns FactionComponent subobject **/
	FORCEINLINE class USF_CharacterFactionComponent* GetFactionComponent() const { return CharacterFactionComponent; }
	/** Returns StateComponent subobject **/
	FORCEINLINE class USF_CharacterStateComponent* GetCharacterStateComponent() const { return CharacterStateComponent; }
	/** Returns TargetSystem subobject **/
	FORCEINLINE class USF_CharacterTargetSystem* GetTargetSystem() const { return TargetSystem; }
	/** Returns CombatComponent subobject **/
	FORCEINLINE class USF_CombatComponent* GetCombatComponent() const { return CombatComponent; }

private:

	/** Faction Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	class USF_CharacterFactionComponent* CharacterFactionComponent;

	/** State Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	class USF_CharacterStateComponent* CharacterStateComponent;

	/** Target System Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	class USF_CharacterTargetSystem* TargetSystem;

	/** Combat Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	class USF_CombatComponent* CombatComponent;
};

