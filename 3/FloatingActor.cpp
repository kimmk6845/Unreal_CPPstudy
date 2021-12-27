// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingActor.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 1�ܰ�
	// FloatingSpeed = 1.0f;

	// 2�ܰ�
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
	// 1�ܰ�
	// ���͸� �����̷��� ���� ��ġ�� �˾ƾ� ��
	// ���͸� ���Ʒ��� �����̴� �ڵ�
	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));	// ���Ͱ� �󸶳� ���Ʒ��� �������� �ϴ��� ���� ����
	NewLocation.Z += DeltaHeight * 20.0f;
	RunningTime += DeltaTime;	// DeltaTime�� ���� Tick�� ������ Tick �ð�����
	SetActorLocation(NewLocation);
	*/

	/*
	// ���� �ڵ�� ���Ʒ� �����̴� �ӵ��� �ϵ��ڵ��� ��
	// ������Ƽ�� ����� ������ �гο� �����ؼ� ����ϱ� ���� �ڵ�
	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime * FloatingSpeed) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * 20.0f;
	RunningTime += DeltaTime * FloatingSpeed;
	SetActorLocation(NewLocation);
	*/

	// 2�ܰ�
	FVector NewLocation = GetActorLocation();
	float DeltaX = (FMath::Sin(RunningTime.X + DeltaTime * FloatingSpeed.X) - FMath::Sin(RunningTime.X));
	float DeltaY = (FMath::Sin(RunningTime.Y + DeltaTime * FloatingSpeed.Y) - FMath::Sin(RunningTime.Y));
	float DeltaZ = (FMath::Sin(RunningTime.Z + DeltaTime * FloatingSpeed.Z) - FMath::Sin(RunningTime.Z));
	NewLocation += FVector(DeltaX, DeltaY, DeltaZ) * 20.0f;
	RunningTime += DeltaTime * FloatingSpeed;
	SetActorLocation(NewLocation);
}

