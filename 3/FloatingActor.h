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
	// 1�ܰ�
	// ���Ʒ��� �����̱�
	float RunningTime;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)		// �𸮾� �����Ϳ� �����ϱ� ����
	float FloatingSpeed;
	*/

	// 2�ܰ� X��, Y�� ������ �߰�
	FVector RunningTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector FloatingSpeed;
};
