#pragma once

#include "CoreMinimal.h"
#include "C_BasicCharacter.h"
#include "C_FPSProjectile.h"

#include "C_PlayerCharacter.generated.h"

UCLASS()
class FPS_BEGIN_API AC_PlayerCharacter : public AC_BasicCharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* camera;

public:
	AC_PlayerCharacter();

protected:
	//virtual void BeginPlay() override;

public:
	//virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// Character
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		USkeletalMeshComponent* FPSMesh;

	// Gun
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* FPSGun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamePlay")
		FVector MuzzleOffset;	// 발사체 스폰 위치

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		TSubclassOf<AC_FPSProjectile> ProjectileClass;	// Fire가 호출됐을 때 스폰해야 할 발사체의 클래스를 담고 있을 변수

private:
	//// 축매핑
	// 이동
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	// 카메라 회전
	void OnHorizontalLook(float Axis);
	void OnVerticalLook(float Axis);

	//// 액션매핑
	void OnRunning();
	void OffRunning();
	void StartJump();
	void StopJump();

	UFUNCTION()
		void Fire();

	void OnFire();
	void OffFire();
	bool IsFiring;
	FTimerHandle timer;


	// AI 자극
	class UAIPerceptionStimuliSourceComponent* stimulus;
	void setup_stimulus();
};
