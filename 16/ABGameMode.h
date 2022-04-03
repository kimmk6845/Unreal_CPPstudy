#pragma once

#include "ArenaBattle.h"
#include "GameFramework/GameModeBase.h"
#include "ABGameMode.generated.h"

UCLASS()
class ARENABATTLE_API AABGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AABGameMode();

	// �÷��̾ ���ӿ� ����(�α���)�ϸ� ȣ��Ǵ� �Լ�
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
