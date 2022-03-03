#include "InventoryWidget.h"

void UInventoryWidget::NativeConstruct()
{
	Btn0 = Cast<UButton>(GetWidgetFromName(TEXT("Btn0")));
	Btn1 = Cast<UButton>(GetWidgetFromName(TEXT("Btn1")));
	Btn2 = Cast<UButton>(GetWidgetFromName(TEXT("Btn2")));
	Btn3 = Cast<UButton>(GetWidgetFromName(TEXT("Btn3")));
	ItemText0 = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemText0")));
	ItemText1 = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemText1")));
	ItemText2 = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemText2")));
	ItemText3 = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemText3")));

}
