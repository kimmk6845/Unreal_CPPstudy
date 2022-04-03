#pragma once

#include "ArenaBattle.h"
#include "GameFramework/PlayerController.h"
#include "ABPlayerController.generated.h"

UCLASS()
class ARENABATTLE_API AABPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	// 컨트롤러 생성 시점에 호출되는 함수
	virtual void PostInitializeComponents() override;

	// 폰에 빙의를 진행하는 시점에 호출되는 함수
	virtual void OnPossess(APawn* aPawn) override;
};
