// 헤더와 CPP 이동 단축기는 Ctrl + K, Ctrl + O

#include "C01_Property.h"

AC01_Property::AC01_Property()
{
	PrimaryActorTick.bCanEverTick = true;

	C = 30;		// 생성자에 초기화를 하나 헤더에서 초기화를 하나 똑같음
}

void AC01_Property::BeginPlay()
{
	Super::BeginPlay();

	//// 접두어로 F는 구조체
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

