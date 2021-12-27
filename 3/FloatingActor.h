// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingActor.generated.h"

UCLASS()
class QUICKSTART_API AFloatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*
	// 1단계
	// 위아래로 움직이기
	float RunningTime;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)		// 언리얼 에디터에 공개하기 위함
	float FloatingSpeed;
	*/

	// 2단계 X축, Y축 움직임 추가
	FVector RunningTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector FloatingSpeed;
};
