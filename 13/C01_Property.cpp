// ����� CPP �̵� ������ Ctrl + K, Ctrl + O

#include "C01_Property.h"

AC01_Property::AC01_Property()
{
	PrimaryActorTick.bCanEverTick = true;

	C = 30;		// �����ڿ� �ʱ�ȭ�� �ϳ� ������� �ʱ�ȭ�� �ϳ� �Ȱ���
}

void AC01_Property::BeginPlay()
{
	Super::BeginPlay();

	//// ���ξ�� F�� ����ü
	//FString str;
	//str.Append("A: ");
	//str.Append(FString::FromInt(A));
	//str.Append(", B: ");
	//str.Append(FString::FromInt(B));
	//str.Append(", C: ");
	//str.Append(FString::FromInt(C));
	//str.Append(", Test: ");
	//str.Append(FString::FromInt(Test));

	//GLog->Log(str);
}

void AC01_Property::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

