// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ClickMovePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CLICKMOVE_API AClickMovePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AClickMovePlayerController();	// ������
	
private:
	bool bClickLeftMouse;	// ���� �� true, �� �� false
	
	void InputLeftMouseButtonPressed();
	void InputLeftMouseButtonReleased();

	// Ŭ���� ��ġ�� �̵���Ű��
	void SetNewDestination(const FVector Destination);

	void MoveToMouseCursor();

	virtual void SetupInputComponent() override;

	virtual void PlayerTick(float DeltaTime) override;	// MoveToMouseCursor�� �ǽð����� ȣ���ϱ� ���� Tick
};
