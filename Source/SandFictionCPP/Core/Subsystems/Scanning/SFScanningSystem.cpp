// Fill out your copyright notice in the Description page of Project Settings.


#include "SFScanningSystem.h"

void USFScanningSystem::AddScannedIdentity(const FGameplayTag IdentityTag)
{
	ScannedIdentities.AddUnique(IdentityTag);

	for (const auto ScanComponent : ScanTargetArray)
	{
		if (ScanComponent->ScanIdentity == IdentityTag)
		{
			ScanComponent->Deactivate();
		}
	}
}

void USFScanningSystem::RemoveScannedIdentity(const FGameplayTag IdentityTag)
{
	ScannedIdentities.Remove(IdentityTag);
}

void USFScanningSystem::RegisterScanTargetComponent(USF_ScanTargetComponent* ScanTarget)
{
	ScanTargetArray.AddUnique(ScanTarget);
}

void USFScanningSystem::UnRegisterScanTargetComponent(USF_ScanTargetComponent* ScanTarget)
{
	ScanTargetArray.Remove(ScanTarget);
}
