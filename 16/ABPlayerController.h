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
	// ��Ʈ�ѷ� ���� ������ ȣ��Ǵ� �Լ�
	virtual void PostInitializeComponents() override;

	// ���� ���Ǹ� �����ϴ� ������ ȣ��Ǵ� �Լ�
	virtual void OnPossess(APawn* aPawn) override;
};
