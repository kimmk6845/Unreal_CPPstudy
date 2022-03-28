#include "TurretWidget.h"

void UTurretWidget::NativeConstruct()
{
	occupyingBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("occupyingBar")));
}

void UTurretWidget::SetOccupyBar(float value)
{
	if (IsValid(occupyingBar))
	{
		occupyingBar->SetPercent(value / 100);
	}
}