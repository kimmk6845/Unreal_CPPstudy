// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Engine/Classes/Particles/ParticleSystemComponent.h>
#include "Fire.generated.h"

UCLASS()
class VARIABLE_TIMER_EVENT_API AFire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* FireParticle;

	UPROPERTY(EditAnywhere)
	int8 FireTime;

	FTimerHandle FireTimerHandle;

	// 파티클이 연소시간동안 타들어가게 하는 함수
	void Combustion();

	// 이벤트가 실행되면 연소시간을 0으로 만들고 파티클을 끄는 함수
	UFUNCTION(BlueprintCallable)
	void OffFire();
};
