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

// BlueprintNativeEvent�� ���α׷��Ӱ� ����� ������ �� ����
void AMyActor::CallFromCpp_Implementation()
{
	str.Append(TEXT("_Implementation"));
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	// �����̳ʰ� ���� ��� �׽�Ʈ
	CallFromCPP();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// DamagePerSecond�� TotalDamage�� DamageTimeInSeconds�� ���ϴ� �Լ�
void AMyActor::FunctionName()
{

}

void AMyActor::CalculateDPS()
{	
	// �𸮾� �����Ϳ��� �� ������ ���� �����ϸ� ��ٷ� DamagePerSecond�� ���� ����Ǵ� ���� Ȯ���� �� ����
	DamagePerSecond = TotalDamage / DamageTimeInSeconds;
}

void AMyActor::PostInitProperties()
{
	/* �θ�Ŭ������ �Լ��� �ٽ� ȣ������� �θ�Ŭ�������� ó���ϴ� �۾���
	������� �ʾ� ������ �߻����� ���� */
	Super::PostInitProperties();	
	CalculateDPS();
}

void AMyActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	CalculateDPS();
	Super::PostEditChangeProperty(PropertyChangedEvent);
}