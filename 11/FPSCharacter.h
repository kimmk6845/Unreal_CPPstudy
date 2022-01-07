// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Engine/Classes/Camera/CameraComponent.h>
#include "FPSProjectile.h"
#include "FPSCharacter.generated.h"

UCLASS()
class FPSPROJECT_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// 축 매핑 (이동)
	UFUNCTION()
	void MoveForward(float AxisValue);

	UFUNCTION()
	void MoveRight(float AxisValue);

	// 액션 매핑 (점프 함수)
	UFUNCTION()
		void StartJump();

	UFUNCTION()
		void StopJump();

	// (발사체 발사 함수)
	UFUNCTION()
		void Fire();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamePlay")
		FVector MuzzleOffset;	// 발사체 스폰 위치

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		TSubclassOf<AFPSProjectile> ProjectileClass;	// Fire가 호출됐을 때 스폰해야 할 발사체의 클래스를 담고 있을 변수


	// 카메라 조정
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FPSCameraComponent;


	// 일인칭 메시
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		USkeletalMeshComponent* FPSMesh;

};
