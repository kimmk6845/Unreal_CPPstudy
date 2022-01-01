// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Engine/Classes/Components/StaticMeshComponent.h>
#include "Door.generated.h"

UCLASS()
class VARIABLE_TIMER_EVENT_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 문 메시
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DoorMesh;

	// 문이 열렸다가 닫히는 시간 표시하는 변수
	UPROPERTY(EditAnywhere)
	float CloseTime;

	// 문이 열리고 닫히는 과정을 표현할 변수
	float DoorDeltaTime;

	// 문이 열렸는지
	bool bOpen;

	// 타이머 관리
	FTimerHandle DoorTimerHandle;

	// 문의 원래 회전 상태를 저장
	FRotator OriginRotation;

	// 문을 열고 닫는 함수
	void Open();
	void Close();

};
