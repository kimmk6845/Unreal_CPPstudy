#include "DamageRecieveWidget.h"

void UDamageRecieveWidget::NativeConstruct()
{
	Super::NativeConstruct();

	blood = Cast<UImage>(GetWidgetFromName(TEXT("blood")));

}
