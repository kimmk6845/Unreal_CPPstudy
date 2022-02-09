#include "FPS_BeginGameModeBase.h"
#include "Global.h"
AFPS_BeginGameModeBase::AFPS_BeginGameModeBase()
{
	// 케릭터 적용
	// Blueprint'/Game/Blueprints/BP_C_PlayerCharacter.BP_C_PlayerCharacter'
	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/Blueprints/BP_C_PlayerCharacter.BP_C_PlayerCharacter_C'");
}