// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraDirector.generated.h"

USTRUCT(Atomic,BlueprintType)
struct FChangeCameraData {
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeBetweenCameraChanges;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SmoothBlendTime;
};

UCLASS()
class CAMERACONTROL_API ACameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraDirector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//// 카메라 제어(1단계)

	//UPROPERTY(EditAnywhere)
	//AActor* CameraOne;

	//UPROPERTY(EditAnywhere)
	//AActor* CameraTwo;

	//UPROPERTY(EditAnywhere)
	//float TimeToNextCameraChange;

	// ------------------------------------------

	//// 배열을 이용한 카메라 제어(도전과제)

	//UPROPERTY(EditAnywhere)
	//TArray<AActor*> Cameras;	// C++ 언리얼 프로그래밍에서 TArray라는 배열 클래스를 사용함

	//int32 NowCameraIndex;	// 현재 사용하고 있는 카메라의 번호 저장

	//UPROPERTY(EditAnywhere)
	//float TimeToNextCameraChange;

	// ------------------------------------------

	//// 구조체를 이용한 카메라 제어

	UPROPERTY(EditAnywhere)
	TArray<FChangeCameraData> Cameras;

	int32 NowCameraIndex;

	UPROPERTY(EditAnywhere)
	float TimeToNextCameraChange;
};
