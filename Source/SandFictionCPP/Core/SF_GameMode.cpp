// Copyright Epic Games, Inc. All Rights Reserved.

#include "SF_GameMode.h"

#include "SF_HUD.h"
#include "Kismet/GameplayStatics.h"
#include "SandFictionCPP/Character/SF_PlayerController.h"
#include "UObject/ConstructorHelpers.h"

ASF_GameMode::ASF_GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASF_PlayerController::StaticClass();
	HUDClass = ASF_HUD::StaticClass();
	bUseSeamlessTravel = true;
	/*
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_Character"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/BP_PlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
	*/
}


void ASF_GameMode::TravelToMap(FString MapName)
{
	NextLevelName = MapName;
	StartLoadingScreenFadeDelay();
}

void ASF_GameMode::ReturnToSpaceship()
{
	NextLevelName = "/Game/Maps/Spaceship/Map_Spaceship";
	StartLoadingScreenFadeDelay();
}

void ASF_GameMode::StartLoadingScreenFadeDelay()
{
	if (const auto PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		if (const auto HUD = Cast<ASF_HUD>(PC->GetHUD()))
		{
			const float FadeTime = HUD->ShowLoadingScreen();
			if (GetWorld())
			{
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,  &ASF_GameMode::OpenLevelAfterLoadingScreenFade, FadeTime);
			}
		}
	}
}

void ASF_GameMode::OpenLevelAfterLoadingScreenFade()
{
	if (GetWorld())
	{
		GetWorld()->ServerTravel(NextLevelName, true);
	}
}


void ASF_GameMode::GenericPlayerInitialization(AController* C)
{
	Super::GenericPlayerInitialization(C);

	if (const auto PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		if (const auto HUD = Cast<ASF_HUD>(PC->GetHUD()))
		{
			HUD->HideLoadingScreen();
		}
	}
}

void ASF_GameMode::PostSeamlessTravel()
{
	Super::PostSeamlessTravel();

	if (const auto PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		if (const auto HUD = Cast<ASF_HUD>(PC->GetHUD()))
		{
			HUD->HideLoadingScreen();
		}
	}
}
