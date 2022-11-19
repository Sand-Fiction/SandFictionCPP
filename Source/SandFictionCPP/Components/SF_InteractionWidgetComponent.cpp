// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_InteractionWidgetComponent.h"
#include "SF_InteractableComponent.h"
#include "SF_InteractionWidget.h"
#include "Kismet/GameplayStatics.h"
#include "SandFictionCPP/Core/SF_GameInstance.h"

USF_InteractionWidgetComponent::USF_InteractionWidgetComponent()
{
	SetCastShadow(false);
	SetWidgetSpace(EWidgetSpace::Screen);
	SetDrawAtDesiredSize(true);
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (const auto GameInstance = Cast<USF_GameInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		SetWidgetClass(GameInstance->InteractionWidgetClass);
	}
}

void USF_InteractionWidgetComponent::BindStatusChange()
{
	InteractableComponent->OnStatusChanged.AddDynamic(this, &USF_InteractionWidgetComponent::OnStatusChanged);
}

void USF_InteractionWidgetComponent::OnStatusChanged()
{
	if (const auto InteractionWidget = Cast<USF_InteractionWidget>(GetUserWidgetObject()))
	{
		InteractionWidget->InteractableComponent = InteractableComponent;
		InteractionWidget->UpdateWidget();
	}
}
