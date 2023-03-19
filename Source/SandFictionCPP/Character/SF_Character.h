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

	/** Returns FactionComponent SubObject **/
	FORCEINLINE class USF_CharacterFactionComponent* GetFactionComponent() const { return CharacterFactionComponent; }
	/** Returns StateComponent SubObject **/
	FORCEINLINE class USF_CharacterStateComponent* GetCharacterStateComponent() const { return CharacterStateComponent; }
	/** Returns CombatComponent SubObject **/
	FORCEINLINE class USF_CombatComponent* GetCombatComponent() const { return CombatComponent; }

	UFUNCTION(BlueprintCallable)
	void SetIsCharging(bool IsCharging);

	UFUNCTION(BlueprintCallable)
	bool GetIsCharging();

private:

	/** Faction Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	class USF_CharacterFactionComponent* CharacterFactionComponent;

	/** State Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	class USF_CharacterStateComponent* CharacterStateComponent;

	/** Combat Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	class USF_CombatComponent* CombatComponent;

	UPROPERTY(BlueprintReadWrite, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	bool bIsCharging;

	UPROPERTY()
	float ChargingSpeed = 750.f;

	UPROPERTY()
	float DefaultSpeed;

protected:

	UFUNCTION()
	virtual void StartDeath();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveStartDeath();

	virtual void BeginPlay() override;

	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) override;

};
