// Copyright Epic Games, Inc. All Rights Reserved.

#include "SF_GameMode.h"
#include "SandFictionCPP/Character/SF_PlayerController.h"
#include "UObject/ConstructorHelpers.h"

ASF_GameMode::ASF_GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASF_PlayerController::StaticClass();

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