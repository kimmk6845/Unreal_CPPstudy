// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	// Tick 함수 제거
	//PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.bCanEverTick = true;
	
	// 로그 출력
	UE_LOG(LogTemp, Log, TEXT("Constructor"));

	// 프로퍼티 초기화
	TotalDamage = 200;
	DamageTimeInSeconds = 1.0f;
	CharacterName = TEXT("CPP_Actor");
	bAttackable = true;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Log, TEXT("BeginPlay"));

}

//// Called every frame
//void AMyActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}


// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Log, TEXT("Tick"));
}
