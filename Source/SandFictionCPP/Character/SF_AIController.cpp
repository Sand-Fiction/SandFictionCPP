// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_AIController.h"

#include "Perception/AIPerceptionComponent.h"


ASF_AIController::ASF_AIController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
}
