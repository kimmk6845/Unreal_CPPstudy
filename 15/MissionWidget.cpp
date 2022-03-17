#include "MissionWidget.h"

void UMissionWidget::NativeConstruct()
{
	missionText = Cast<UTextBlock>(GetWidgetFromName(TEXT("missionText")));
	infoText = Cast<UTextBlock>(GetWidgetFromName(TEXT("infoText")));
	TurretText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TurretText")));
	bindText = Cast<UTextBlock>(GetWidgetFromName(TEXT("bindText")));
}

void UMissionWidget::SetMissionText(int32 turretNum)
{
	if (IsValid(bindText))
	{
		bindText->SetText(FText::FromString(FString::FromInt(turretNum)));
	}
}