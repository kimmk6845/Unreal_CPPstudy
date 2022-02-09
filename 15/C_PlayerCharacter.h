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
		FVector MuzzleOffset;	// �߻�ü ���� ��ġ

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		TSubclassOf<AC_FPSProjectile> ProjectileClass;	// Fire�� ȣ����� �� �����ؾ� �� �߻�ü�� Ŭ������ ��� ���� ����

private:
	//// �����
	// �̵�
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	// ī�޶� ȸ��
	void OnHorizontalLook(float Axis);
	void OnVerticalLook(float Axis);

	//// �׼Ǹ���
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


	// AI �ڱ�
	class UAIPerceptionStimuliSourceComponent* stimulus;
	void setup_stimulus();
};
