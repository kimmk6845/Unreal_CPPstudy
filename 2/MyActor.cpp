// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	TotalDamage = 200;
	DamageTimeInSeconds = 1.0f;

	str = TEXT("TEST");
}

// BlueprintNativeEvent는 프로그래머가 기능을 구현할 수 있음
void AMyActor::CallFromCpp_Implementation()
{
	str.Append(TEXT("_Implementation"));
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	// 디자이너가 만든 기능 테스트
	CallFromCPP();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// DamagePerSecond를 TotalDamage와 DamageTimeInSeconds로 구하는 함수
void AMyActor::FunctionName()
{

}

void AMyActor::CalculateDPS()
{	
	// 언리얼 에디터에서 두 변수의 값을 변경하면 곧바로 DamagePerSecond의 값이 변경되는 것을 확인할 수 있음
	DamagePerSecond = TotalDamage / DamageTimeInSeconds;
}

void AMyActor::PostInitProperties()
{
	/* 부모클래스의 함수를 다시 호출해줘야 부모클래스에서 처리하는 작업이
	실행되지 않아 문제가 발생하지 않음 */
	Super::PostInitProperties();	
	CalculateDPS();
}

void AMyActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	CalculateDPS();
	Super::PostEditChangeProperty(PropertyChangedEvent);
}