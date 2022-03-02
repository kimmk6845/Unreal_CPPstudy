#include "CGameModeBase.h"
#include "FPSCharacter.h"
#include "FPSHUD.h"
#include "Global.h"

ACGameModeBase::ACGameModeBase()
{
	//// ���α׷��� �������� ������ ���� �ذ��ϱ� ������ �����Ϳ��� ���� ����
	//CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/_My/Blueprints/BP_FPSCharacter.BP_FPSCharacter_C'");

	HUDClass = AFPSHUD::StaticClass();	
}

void ACGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(StateClass))	// hp, �Ѿ� ���� ����
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
