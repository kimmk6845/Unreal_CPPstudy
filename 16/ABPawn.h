#pragma once

#include "ArenaBattle.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "ABPawn.generated.h"

UCLASS()
class ARENABATTLE_API AABPawn : public APawn
{
	GENERATED_BODY()

private:
	// �����
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

public:
	AABPawn();

	UPROPERTY(VisibleAnywhere, Category = "Collision")
		UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere, Category = "Visual")
		USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
		UFloatingPawnMovement* Movement;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
		UCameraComponent* Camera;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// �� ���� ������ ȣ��Ǵ� �Լ�
	virtual void PostInitializeComponents() override;

	// ���Ǹ� �����ϴ� ������ ȣ��Ǵ� �Լ�
	virtual void PossessedBy(AController* NewController) override;
};
