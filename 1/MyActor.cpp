// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "CPP_Tutorial.h"

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
	CharacterName = TEXT("CPP액터");
	bAttackable = true;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Log, TEXT("BeginPlay"));
	UE_LOG(LogTemp, Error, TEXT("Error Message"));			// 빨
	UE_LOG(LogTemp, Warning, TEXT("Warning Message"));		// 노
	UE_LOG(LogTemp, Display, TEXT("Display Message"));		// 흰

	// 사용자 로그 카테고리를 생성해 어떤 카테고리에서 오류가 발생했는지 알 수 있음
	UE_LOG(MyLogCategory, Log, TEXT("My Category Log"));

	// 변수를 이용한 로그 출력
	FString Character_name = TEXT("TEST");
	UE_LOG(LogTemp, Log, TEXT("Character Name: %s"), *Character_name);
	bool isAttackable = true;
	UE_LOG(LogTemp, Log, TEXT("Is Attackable: %s"), isAttackable ? TEXT("true") : TEXT("false"));
	int hp = 100;
	UE_LOG(LogTemp, Log, TEXT("HP: %d"), hp);
	float AttackSpeed = 1.0f;
	UE_LOG(LogTemp, Log, TEXT("Attack Speed: %f"), AttackSpeed);
	FVector CharacterLocation = GetActorLocation();
	UE_LOG(LogTemp, Log, TEXT("Position: %s"), CharacterLocation.ToString());
	
	UE_LOG(LogTemp, Log, TEXT("Character Name: %s, HP: %d, Attack Speed: %f"), *Character_name, hp, AttackSpeed);

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

	//// Tick마다 로그가 출력됨
	// UE_LOG(LogTemp, Log, TEXT("Tick"));
}
