// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class CPP_TUTORIAL_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();


	// 변수 만들기
	UPROPERTY()
	int32 IntVariable;

	//// 플랫폼마다 길이가 달라질 수 있음
	//short s;
	//int i;
	//long l;
	
	// 고정길이 사용
	int8 i8;	// 127 ~ -128
	int16 i16; 
	int32 i32;
	int64 i64;

	// 양수만 사용
	uint8 ui8;	// 0 ~ 255
	uint16 ui16;
	uint32 ui32;
	uint64 ui64;
	


	// 부동소수점
	float f;
	double d;

	// 문자열
	FString str;	// 가변길이
	
	// 논리변수
	bool b;

public:
	// 사용 예
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	int32 TotalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageTimeInSeconds;

	// 블루프린트에서 읽기만 가능, 프로퍼티를 모든 프로퍼티창에서 보이지만 편집 불가, 휘발성 프로퍼티로 저장되지 않음
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Transient,Category = "Damage")
	float DamagePerSecond;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAttackable;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	//// Tick 함수를 사용하지 않으면 제거함으로써 퍼포먼스를 향상시키기
	//// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
