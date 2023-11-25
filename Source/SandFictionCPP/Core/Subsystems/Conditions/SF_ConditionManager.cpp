// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_ConditionManager.h"

bool USF_ConditionManager::HasCondition(const FGameplayTag ConditionTag) const
{
	return GameplayConditions.Contains(ConditionTag);
}

void USF_ConditionManager::AddCondition(const FGameplayTag ConditionTag)
{
	GameplayConditions.AddUnique(ConditionTag);
}

void USF_ConditionManager::RemoveCondition(const FGameplayTag ConditionTag)
{
	GameplayConditions.Remove(ConditionTag);
}
