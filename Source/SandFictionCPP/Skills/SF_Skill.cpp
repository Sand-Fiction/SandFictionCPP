// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_Skill.h"

#include "SandFictionCPP/Components/SF_CombatComponent.h"

// Sets default values for this component's properties
ASF_Skill::ASF_Skill()
{
	
}

// Called when the game starts
void ASF_Skill::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called when the Component gets destroyed
void ASF_Skill::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	CombatComponent->SpawnedSkill = nullptr;
}

void ASF_Skill::SkillStart_Implementation()
{

}

// Skill despawns when Cooldown ends, so you can use the skill again
void ASF_Skill::SkillEnd()
{
	Destroy();
}

void ASF_Skill::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

