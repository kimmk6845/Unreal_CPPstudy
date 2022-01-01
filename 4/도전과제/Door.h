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

	// �� �޽�
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DoorMesh;

	// ���� ���ȴٰ� ������ �ð� ǥ���ϴ� ����
	UPROPERTY(EditAnywhere)
	float CloseTime;

	// ���� ������ ������ ������ ǥ���� ����
	float DoorDeltaTime;

	// ���� ���ȴ���
	bool bOpen;

	// Ÿ�̸� ����
	FTimerHandle DoorTimerHandle;

	// ���� ���� ȸ�� ���¸� ����
	FRotator OriginRotation;

	// ���� ���� �ݴ� �Լ�
	void Open();
	void Close();

};
