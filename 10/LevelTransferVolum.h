// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelTransferVolum.generated.h"

UCLASS()
class OPENLEVEL_API ALevelTransferVolum : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelTransferVolum();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;	// 콜리전 감지
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FString TransferLevelName;	// 이 액터에 닿았을 때 씬의 이름을 저장

	UPROPERTY()
	class UBoxComponent* TransferVolume;	// 콜리전 영역
};
