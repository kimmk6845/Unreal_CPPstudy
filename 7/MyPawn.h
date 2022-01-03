// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class PLAYERINPUTANDPAWN_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 월드에 배치 가능한 다른 컴포넌트들의 부모 클래스가 되는 컴포넌트
	// 물리 효과를 지원하지 않고 렌더링 기능도 없어 아주 가벼워 계층 구조에서 더미로 활용하기 좋음
	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;	


	// 입력처리
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void StartGrowing();
	void StopGrowing();

	FVector CurrentVelocity;
	bool bGrowing;
};
