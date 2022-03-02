#include "CGameModeBase.h"
#include "FPSCharacter.h"
#include "FPSHUD.h"
#include "Global.h"

ACGameModeBase::ACGameModeBase()
{
	//// 프로그램을 열때마다 에러가 나서 해결하기 전까지 에디터에서 직접 넣음
	//CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/_My/Blueprints/BP_FPSCharacter.BP_FPSCharacter_C'");

	HUDClass = AFPSHUD::StaticClass();	
}

void ACGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(StateClass))	// hp, 총알 상태 위젯
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
