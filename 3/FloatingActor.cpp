// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingActor.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 1단계
	// FloatingSpeed = 1.0f;

	// 2단계
	FloatingSpeed = FVector(1.0f, 1.0f, 1.0f);
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	/*
	// 1단계
	// 액터를 움직이려면 현재 위치를 알아야 함
	// 액터를 위아래로 움직이는 코드
	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));	// 액터가 얼마나 위아래로 움직여야 하는지 값을 구함
	NewLocation.Z += DeltaHeight * 20.0f;
	RunningTime += DeltaTime;	// DeltaTime은 이전 Tick과 현재의 Tick 시간차이
	SetActorLocation(NewLocation);
	*/

	/*
	// 위의 코드는 위아래 움직이는 속도를 하드코딩한 것
	// 프로퍼티를 만들어 디테일 패널에 공개해서 사용하기 위한 코딩
	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime * FloatingSpeed) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * 20.0f;
	RunningTime += DeltaTime * FloatingSpeed;
	SetActorLocation(NewLocation);
	*/

	// 2단계
	FVector NewLocation = GetActorLocation();
	float DeltaX = (FMath::Sin(RunningTime.X + DeltaTime * FloatingSpeed.X) - FMath::Sin(RunningTime.X));
	float DeltaY = (FMath::Sin(RunningTime.Y + DeltaTime * FloatingSpeed.Y) - FMath::Sin(RunningTime.Y));
	float DeltaZ = (FMath::Sin(RunningTime.Z + DeltaTime * FloatingSpeed.Z) - FMath::Sin(RunningTime.Z));
	NewLocation += FVector(DeltaX, DeltaY, DeltaZ) * 20.0f;
	RunningTime += DeltaTime * FloatingSpeed;
	SetActorLocation(NewLocation);
}

