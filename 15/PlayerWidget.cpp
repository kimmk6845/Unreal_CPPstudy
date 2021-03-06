#include "PlayerWidget.h"

UPlayerWidget::UPlayerWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	hp = Cast<UTextBlock>(GetWidgetFromName(TEXT("hp")));
	hpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("hpBar")));
	remainAmmo = Cast<UTextBlock>(GetWidgetFromName(TEXT("remainAmmo")));
	totalAmmo = Cast<UTextBlock>(GetWidgetFromName(TEXT("totalAmmo")));
	staminaBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("staminaBar")));
	pickupText = Cast<UTextBlock>(GetWidgetFromName(TEXT("pickupText")));
	missionText = Cast<UTextBlock>(GetWidgetFromName(TEXT("missionText")));
	infoText = Cast<UTextBlock>(GetWidgetFromName(TEXT("infoText")));
}

void UPlayerWidget::SetHP(float health)
{
	if (IsValid(hp))
	{
		hp->SetText(FText::FromString(FString::FromInt(health)));
	}
}

void UPlayerWidget::SetHPBar(float health)
{
	if (IsValid(hpBar))
	{
		hpBar->SetPercent(health / 100);
	}
}

void UPlayerWidget::SetRemainAmmo(int32 ammo)
{
	if (IsValid(remainAmmo))
	{
		remainAmmo->SetText(FText::FromString(FString::FromInt(ammo)));
	}
}

void UPlayerWidget::SetStamina(float stamina)
{
	if (IsValid(staminaBar))
	{
		staminaBar->SetPercent(stamina / 100);
	}
}

void UPlayerWidget::SetHelpText(FString text)
{
	if (IsValid(pickupText))
	{
		pickupText->SetText(FText::FromString(text));
	}
}

void UPlayerWidget::SetMissionText(int32 turretNum)
{
	if (IsValid(missionText))
	{
		missionText->SetText(FText::FromString(FString::FromInt(turretNum)));
	}
}

void UPlayerWidget::SetInfoText(FString text)
{
	if (IsValid(infoText))
	{
		infoText->SetText(FText::FromString(text));
	}
}