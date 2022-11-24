// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SandFictionCPP/Character/SF_CharacterEnums.h"
#include "SF_CharacterFactionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SANDFICTIONCPP_API USF_CharacterFactionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USF_CharacterFactionComponent();

	UFUNCTION(BlueprintCallable)
	void SetFaction(ECharacterFaction NewFaction);

	UFUNCTION(BlueprintPure)
	bool IsHostile(USF_CharacterFactionComponent* OtherFactionComponent);

	UPROPERTY(EditAnywhere)
	ECharacterFaction Faction;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
