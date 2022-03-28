#include "AdrenalineBuffWidget.h"

void UAdrenalineBuffWidget::NativeConstruct()
{
	BuffOverlay = Cast<UImage>(GetWidgetFromName(TEXT("BuffOverlay")));
}