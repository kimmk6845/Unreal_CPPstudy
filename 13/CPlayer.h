#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

UCLASS()
class UONLINE_CPP_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	// 플레이어 이동 함수
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	// 카메라 회전 함수
	void OnHorizontalLook(float Axis);
	void OnVerticalLook(float Axis);

private:
	// 축 매핑(Running)
	void OnRunning();
	void OffRunning();

};
