// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SFRoomSystem.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "SFRoomActor.generated.h"

UCLASS(Blueprintable)
class SANDFICTIONCPP_API ASFRoomActor : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoundingBox;

	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* Name;
	
public:	
	// Sets default values for this actor's properties
	ASFRoomActor();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag RoomIdentifier;

	UFUNCTION(BlueprintPure)
	FSFRoomStruct GetRoomData() const;

	// Returns true if the BoundingBox of the Actor is fully inside the BoundingBox of the Room
	UFUNCTION(BlueprintPure)
	bool IsActorInsideRoom(const AActor* Actor) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

};
