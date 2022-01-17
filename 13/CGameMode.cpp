#include "CGameMode.h"
#include "Global.h"

ACGameMode::ACGameMode()
{
	//// 블루프린트 클래스 에셋을 불러옴
	// Blueprint'/Game/BP_CPlayer.BP_CPlayer'
	// 주의할 점 = 블루프린트의 클래스 타입을 로딩할 때에는 식별자에 _C를 반드시 붙여줘야 정상적으로 불러짐
	/*
	* 너무 기니까 CHelpers에 정의
	ConstructorHelpers::FClassFinder<APawn> pawn(L"Blueprint'/Game/BP_CPlayer.BP_CPlayer_C'"); // 뒤에 _C를 붙임
	if(pawn.Succeeded())
		pawn.Class

	DefaultPawnClass;
	*/

	// CHelpers 이용
	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/BP_CPlayer.BP_CPlayer_C'");
}