#include "CGameMode.h"
#include "Global.h"

ACGameMode::ACGameMode()
{
	//// �������Ʈ Ŭ���� ������ �ҷ���
	// Blueprint'/Game/BP_CPlayer.BP_CPlayer'
	// ������ �� = �������Ʈ�� Ŭ���� Ÿ���� �ε��� ������ �ĺ��ڿ� _C�� �ݵ�� �ٿ���� ���������� �ҷ���
	/*
	* �ʹ� ��ϱ� CHelpers�� ����
	ConstructorHelpers::FClassFinder<APawn> pawn(L"Blueprint'/Game/BP_CPlayer.BP_CPlayer_C'"); // �ڿ� _C�� ����
	if(pawn.Succeeded())
		pawn.Class

	DefaultPawnClass;
	*/

	// CHelpers �̿�
	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/BP_CPlayer.BP_CPlayer_C'");
}