// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_CombatComponent.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "SF_CharacterFactionComponent.h"
#include "SandFictionCPP/Character/SF_Character.h"
#include "SF_CharacterStateComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "SandFictionCPP/Skills/SF_Skill.h"

// Sets default values for this component's properties
USF_CombatComponent::USF_CombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	ResetAttackCounter();

	HealthRegen = 1;
	HealthMax = 100;
	AttackRange = 150;
	DamageMin = 5;
	DamageMax = 15;

	// ...
}


void USF_CombatComponent::AttackCheck()
{
	// Get Faction Component
	const auto FactionComponent = Cast<ASF_Character>(GetOwner())->GetFactionComponent();

	// Trace Parameters
	const FCollisionShape Sphere = FCollisionShape::MakeSphere(100.0f); // 5M Radius
	TArray<FHitResult> OutResults;
	const auto SweepStart = GetOwner()->GetActorLocation();;
	const auto SweepEnd = SweepStart + (GetOwner()->GetActorForwardVector() * AttackRange);
	constexpr auto TraceChannel = ECollisionChannel::ECC_Pawn;

	// Sphere Trace for Pawns
	if (GetWorld()->SweepMultiByChannel(OutResults, SweepStart, SweepEnd, FQuat::Identity, TraceChannel, Sphere))
	{
		for (const auto HitResult : OutResults)
		{
			if (const auto HitCharacter = Cast<ASF_Character>(HitResult.GetActor()))
			{
				if (HitCharacter->GetFactionComponent()->IsHostile(FactionComponent))
				{
					HitCharacter->GetCombatComponent()->GetHit(this);
				}
			}
		}
	}
}

void USF_CombatComponent::MeleeAttack()
{
	if (const auto OwningCharacter = Cast<ASF_Character>(GetOwner()))
	{
		if (AnimDataTable)
		{
			FString AnimNameString;

			if (OwningCharacter->GetIsCharging())
			{
				AnimNameString = FString::Printf(TEXT("ChargeAttack"));
			}
			else
			{
				if (MaxAttackChain == 0)
				{
					AttackCounter = FMath::RandRange(1, 3);
				}
				else 
					if (AttackCounter >= MaxAttackChain)
					{
						ResetAttackCounter();
						AttackCounter++;
					}
					else
					{
						AttackCounter++;
					}

				AnimNameString = FString::Printf(TEXT("MeleeAttack0%d"), AttackCounter);
			}

			const auto AnimName = FName(AnimNameString);
			const auto AnimData = AnimDataTable->FindRow<FCharacterAnimationData>(AnimName, TEXT("MeleeAttackAnim not found in AnimDT."), true);
			if (AnimData && AnimData->AnimMontage)
			{
				AttachWeapon();
				OwningCharacter->GetCharacterStateComponent()->ChangeCharacterState(ECharacterState::Attacking);
				OwningCharacter->PlayAnimMontage(AnimData->AnimMontage);

				// Call MeleeAttackEnd when Anim finishes
				OwningCharacter->GetCharacterStateComponent()->OnCharacterStateChanged.AddUniqueDynamic(this, &USF_CombatComponent::MeleeAttackEnd);
			}
			else
			{
				ResetAttackCounter();
			}
		}
	}
}

void USF_CombatComponent::MeleeAttackEnd(ECharacterState OldCharacterState, ECharacterState NewCharacterState)
{
	if (NewCharacterState != ECharacterState::Attacking)
	{
		DetachWeapon();
		if (const auto OwningCharacter = Cast<ASF_Character>(GetOwner()))
		{
			OwningCharacter->GetCharacterStateComponent()->OnCharacterStateChanged.RemoveDynamic(this, &USF_CombatComponent::MeleeAttackEnd);
		}
	}
}

void USF_CombatComponent::AttachWeapon()
{
	if (!CurrentWeaponMesh)
	{
		CurrentWeaponMesh = NewObject<UStaticMeshComponent>(GetOwner(), UStaticMeshComponent::StaticClass(), TEXT("Weapon"));
		CurrentWeaponMesh->RegisterComponent();
		if (const auto Character = Cast<ACharacter>(GetOwner()))
		{
			CurrentWeaponMesh->AttachToComponent
			(
				Character->GetMesh(),
				FAttachmentTransformRules::SnapToTargetNotIncludingScale,
				"Weapon_R"
			);
		}

		switch (CombatStance)
		{
			default: CurrentWeaponMesh->SetStaticMesh(MeleeWeapon); break;
			case Melee: CurrentWeaponMesh->SetStaticMesh(MeleeWeapon); break;
			case Ranged:  CurrentWeaponMesh->SetStaticMesh(RangedWeapon); break;
		}
	}
}

void USF_CombatComponent::DetachWeapon()
{
	if (CurrentWeaponMesh)
	{
		CurrentWeaponMesh->DestroyComponent();
		CurrentWeaponMesh = nullptr;
	}
}

void USF_CombatComponent::ResetAttackCounter()
{
	AttackCounter = 0;
}

void USF_CombatComponent::GetHit(USF_CombatComponent* Source)
{
	// ToDo: GetHit Check for Rolling, Blocking etc.

	if (const auto OwningCharacter = Cast<ASF_Character>(GetOwner()))
	{
		// Play GetHit Animation Montage
		if (AnimDataTable)
		{
			const auto AnimData = AnimDataTable->FindRow<FCharacterAnimationData>(TEXT("GettingHit"), TEXT("GettingHit not found in AnimDT."), true);
			if (AnimData && AnimData->AnimMontage)
			{
				// Rotate Character to Source Location 
				FRotator TargetRotation;
				const auto LookAtRotation = UKismetMathLibrary::FindLookAtRotation(OwningCharacter->GetActorLocation(), Source->GetOwner()->GetActorLocation());
				TargetRotation.Yaw = LookAtRotation.Yaw;
				TargetRotation.Pitch = OwningCharacter->GetActorRotation().Pitch;
				TargetRotation.Roll = OwningCharacter->GetActorRotation().Roll;
				OwningCharacter->SetActorRotation(TargetRotation);

				OwningCharacter->GetCharacterStateComponent()->ChangeCharacterState(ECharacterState::GettingHit);
				OwningCharacter->PlayAnimMontage(AnimData->AnimMontage);
				OwningCharacter->GetMesh()->GetAnimInstance()->OnMontageEnded.AddUniqueDynamic(this, &USF_CombatComponent::GetHitEnd);
			}
		}

		// Calculate Damage
		TakeDamage(Source);
	}
}

void USF_CombatComponent::GetHitEnd(UAnimMontage* Montage, bool bBInterrupted)
{
	if (const auto OwningCharacter = Cast<ASF_Character>(GetOwner()))
	{
		OwningCharacter->GetMesh()->GetAnimInstance()->OnMontageEnded.RemoveDynamic(this, &USF_CombatComponent::GetHitEnd);
		OwningCharacter->GetCharacterStateComponent()->ChangeCharacterState(ECharacterState::Idle);
	}
}

void USF_CombatComponent::UseSkill()
{
	if (const auto OwningCharacter = Cast<ASF_Character>(GetOwner()))
	{
		// Spawn Current SkillComponent
		if (!SpawnedSkill)
		{
			const FVector SpawnLocation = GetOwner()->GetActorLocation();
			const FRotator SpawnRotation = GetOwner()->GetActorRotation();
			SpawnedSkill = GetWorld()->SpawnActor<ASF_Skill>(CurrentSkillClass, FTransform(SpawnRotation, SpawnLocation));
			SpawnedSkill->CombatComponent = this;
			SpawnedSkill->SkillStart();

			// Animation
			if (AnimDataTable)
			{
				// Replace with AnimMontage from "CurrentSkillClass->AnimMontage"
				const auto AnimData = AnimDataTable->FindRow<FCharacterAnimationData>(TEXT("Skill"), TEXT("Skill not found in AnimDT."), true);
				if (AnimData && AnimData->AnimMontage)
				{
					OwningCharacter->PlayAnimMontage(AnimData->AnimMontage);
					OwningCharacter->GetCharacterStateComponent()->ChangeCharacterState(ECharacterState::Attacking);
				}
			}
		}
		else
		{
			// Skill is still spawned / on Cooldown
		}		
	}
}

void USF_CombatComponent::StartKillOwner()
{
	if (const auto OwningCharacter = Cast<ASF_Character>(GetOwner()))
	{
		// If Owner is AI -> Stop Brain Logic
		if (const auto AIController = Cast<AAIController>(OwningCharacter->GetController()))
		{
			if (AIController->GetBrainComponent())
			{
				AIController->GetBrainComponent()->Cleanup();
			}
		}

		// Death Animation
		if (AnimDataTable)
		{
			const auto AnimData = AnimDataTable->FindRow<FCharacterAnimationData>(TEXT("Death"), TEXT("Skill not found in AnimDT."), true);
			if (AnimData && AnimData->AnimMontage)
			{
				OwningCharacter->PlayAnimMontage(AnimData->AnimMontage);
				OwningCharacter->GetCharacterStateComponent()->ChangeCharacterState(ECharacterState::Dying);
			}
		}

		// ToDo: Handle Character Death in Character itself (Bind to OnStateChange-Dying)
		
		// Disable Collision
		OwningCharacter->SetActorEnableCollision(false);

		// Enable Ragdoll
		OwningCharacter->GetMesh()->SetAllBodiesSimulatePhysics(true);
		OwningCharacter->GetMesh()->SetSimulatePhysics(true);
		OwningCharacter->GetMesh()->WakeAllRigidBodies();

		// ToDo: Spawn VFX Effect
	}

	// ToDo: Delay until Anim / VFX played
	// EndKillOwner();
}

void USF_CombatComponent::EndKillOwner(UAnimMontage* AnimMontage, bool Finished)
{
	GetOwner()->Destroy();
}

void USF_CombatComponent::TakeDamage(USF_CombatComponent* Source)
{
	const auto Damage = FMath::RandRange(Source->DamageMin, Source->DamageMax);
	SetCurrentHealth(HealthCurrent - Damage);
	OnDamageTaken.Broadcast(Damage, Source);
}

void USF_CombatComponent::SetCurrentHealth(float NewCurrentHealth)
{
	HealthCurrent = FMath::Clamp(NewCurrentHealth, 0.0f, HealthMax);
	OnCurrentHealthChanged.Broadcast(NewCurrentHealth);

	if (FMath::IsNearlyZero(HealthCurrent) || HealthCurrent <= 0.0f)
	{
		StartKillOwner();
		OnCharacterDied.Broadcast();
	}
}

// Called when the game starts
void USF_CombatComponent::BeginPlay()
{
	Super::BeginPlay();


	SetCurrentHealth(HealthMax);
	SetComponentTickEnabled(false);

	// ...
	
}


// Called every frame
void USF_CombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// .ToDo: Regen Health here...
}

