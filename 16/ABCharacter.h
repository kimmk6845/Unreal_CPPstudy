#pragma once

#include "ArenaBattle.h"
#include "GameFramework/Character.h"
#include "ABCharacter.generated.h"

UCLASS()
class ARENABATTLE_API AABCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	// 축매핑
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Turn(float AxisValue);
	void LookUp(float AxisValue);

	// 액션매핑
	void ViewChange();			// 시점 변환
	void Attack();


	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = "Attack", meta = (AllowPrivateAccess = true))
		bool IsAttacking;

	UPROPERTY()
		class UABAnimInstance* ABAnim;

	// 콤보 변수
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = "Attack", meta = (AllowPrivateAccess = true))
		bool CanNextCombo;
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = "Attack", meta = (AllowPrivateAccess = true))
		bool IsComboInputOn;
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = "Attack", meta = (AllowPrivateAccess = true))
		int32 CurrentCombo;
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = "Attack", meta = (AllowPrivateAccess = true))
		int32 MaxCombo;

public:
	AABCharacter();

	UPROPERTY(VisibleAnywhere, Category = "Camera")
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
		UCameraComponent* Camera;

protected:
	virtual void BeginPlay() override;

	enum class EControlMode
	{
		GTA,
		DIABLO
	};

	void SetControlMode(EControlMode ControlMode);			// 시점 적용 함수
	EControlMode CurrentControlMode = EControlMode::GTA;
	FVector DirectionToMove = FVector::ZeroVector;

	// 시점 변환을 부드럽게 하기 위한 변수
	float ArmLengthTo = 0.0f;
	FRotator ArmRotationTo = FRotator::ZeroRotator;
	float ArmLengthSpeed = 0.0f;
	float ArmRotationSpeed = 0.0f;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
		void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted); // 델리게이트
	
	// 콤보
	void AttackStartComboState();
	void AttackEndComboState();
};
