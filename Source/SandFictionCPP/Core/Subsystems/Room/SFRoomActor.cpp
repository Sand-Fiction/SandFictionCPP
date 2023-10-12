// Fill out your copyright notice in the Description page of Project Settings.


#include "SFRoomActor.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ASFRoomActor::ASFRoomActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	BoundingBox = CreateDefaultSubobject<UBoxComponent>("RoomBoundingBox");
	BoundingBox->SetupAttachment(RootComponent);
	BoundingBox->InitBoxExtent(FVector(200, 200, 150));
	BoundingBox->SetLineThickness(5.f);

	Name = CreateDefaultSubobject<UTextRenderComponent>("RoomName");
	Name->SetupAttachment(RootComponent);
	Name->SetText(FText::FromString("RoomName"));
	Name->SetHiddenInGame(true);
	Name->SetHorizontalAlignment(EHTA_Center);
	Name->SetVerticalAlignment(EVRTA_TextCenter);
	Name->SetWorldSize(48.f);
}

FSFRoomStruct ASFRoomActor::GetRoomData() const
{
	FSFRoomStruct RoomData = FSFRoomStruct();

	if (!GetGameInstance())
	{
		return RoomData;
	}

	if (const auto RoomSystem = GetGameInstance()->GetSubsystem<USFRoomSystem>())
	{
		RoomSystem->GetRoomDataByTag(RoomIdentifier, RoomData);
	}
	return RoomData;
}

bool ASFRoomActor::IsActorInsideRoom(const AActor* Actor) const
{
	const FBox RoomBoundingBox = GetComponentsBoundingBox();
	const FBox ActorBoundingBox = Actor->GetComponentsBoundingBox();
	const bool ReturnValue = RoomBoundingBox.IsInside(ActorBoundingBox);
	return ReturnValue;
}

// Called when the game starts or when spawned
void ASFRoomActor::BeginPlay()
{
	Super::BeginPlay();

	if (const auto RoomSystem = GetGameInstance()->GetSubsystem<USFRoomSystem>())
	{
		RoomSystem->InitializeActorsInRoom(RoomIdentifier);
	}
}

// Called every frame
void ASFRoomActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASFRoomActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (RoomIdentifier.IsValid())
	{
		Name->SetText(FText::FromName(RoomIdentifier.GetTagName()));
	}
	else
	{
		Name->SetText(FText::FromString("RoomName"));
	}
}

void ASFRoomActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!OtherActor)
	{
		return;
	}

	if (const auto RoomSystem = GetGameInstance()->GetSubsystem<USFRoomSystem>())
	{
		if (OtherActor == UGameplayStatics::GetPlayerPawn(this, 0))
		{
			RoomSystem->CurrentRoom = RoomIdentifier;
		}
	}

	Super::NotifyActorBeginOverlap(OtherActor);
}

void ASFRoomActor::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (!OtherActor)
	{
		return;
	}

	if (const auto RoomSystem = GetGameInstance()->GetSubsystem<USFRoomSystem>())
	{
		if (OtherActor == UGameplayStatics::GetPlayerPawn(this, 0))
		{
			RoomSystem->CurrentRoom = FGameplayTag();
		}
	}

	Super::NotifyActorEndOverlap(OtherActor);
}

