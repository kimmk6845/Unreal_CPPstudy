#pragma once

#include "ArenaBattle.h"
#include "GameFramework/Character.h"
#include "ABCharacter.generated.h"

UCLASS()
class ARENABATTLE_API AABCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	// �����
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Turn(float AxisValue);
	void LookUp(float AxisValue);

	// �׼Ǹ���
	void ViewChange();			// ���� ��ȯ
	void Attack();


	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = "Attack", meta = (AllowPrivateAccess = true))
		bool IsAttacking;

	UPROPERTY()
		class UABAnimInstance* ABAnim;

	// �޺� ����
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

	void SetControlMode(EControlMode ControlMode);			// ���� ���� �Լ�
	EControlMode CurrentControlMode = EControlMode::GTA;
	FVector DirectionToMove = FVector::ZeroVector;

	// ���� ��ȯ�� �ε巴�� �ϱ� ���� ����
	float ArmLengthTo = 0.0f;
	FRotator ArmRotationTo = FRotator::ZeroRotator;
	float ArmLengthSpeed = 0.0f;
	float ArmRotationSpeed = 0.0f;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
		void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted); // ��������Ʈ
	
	// �޺�
	void AttackStartComboState();
	void AttackEndComboState();
};
