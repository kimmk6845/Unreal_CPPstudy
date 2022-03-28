#include "CGameModeBase.h"

ACGameModeBase::ACGameModeBase()
{
	HUDClass = AFPSHUD::StaticClass();	

}

void ACGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(StateClass))	// hp, ÃÑ¾Ë »óÅÂ À§Á¬
	{
		StateWidget = Cast<UPlayerWidget>(CreateWidget(GetWorld(), StateClass));

		if (StateWidget != nullptr)
		{
			StateWidget->AddToViewport();
		}
	}
}

UPlayerWidget* ACGameModeBase::GetPlayerWidget() const
{
	return StateWidget;
}