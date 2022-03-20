#include "MenuWidget.h"

void UMenuWidget::NativeConstruct()
{
	btnStart = Cast<UButton>(GetWidgetFromName(TEXT("btnStart")));
	btnExit = Cast<UButton>(GetWidgetFromName(TEXT("btnExit")));

	btnStart->OnClicked.AddDynamic(this, &UMenuWidget::GameStartClick);
	btnExit->OnClicked.AddDynamic(this, &UMenuWidget::ExitClick);

}

void UMenuWidget::GameStartClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), "02_Zombie");
}

void UMenuWidget::ExitClick()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
