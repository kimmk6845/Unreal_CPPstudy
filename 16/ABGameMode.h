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

	// 플레이어가 게임에 입장(로그인)하면 호출되는 함수
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
