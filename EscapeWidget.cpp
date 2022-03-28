#include "EscapeWidget.h"

void UEscapeWidget::NativeConstruct()
{
	WinText = Cast<UTextBlock>(GetWidgetFromName(TEXT("WinText")));
}