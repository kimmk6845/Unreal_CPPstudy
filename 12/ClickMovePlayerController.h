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
	AClickMovePlayerController();	// 생성자
	
private:
	bool bClickLeftMouse;	// 누를 때 true, 뗄 때 false
	
	void InputLeftMouseButtonPressed();
	void InputLeftMouseButtonReleased();

	// 클릭한 위치로 이동시키기
	void SetNewDestination(const FVector Destination);

	void MoveToMouseCursor();

	virtual void SetupInputComponent() override;

	virtual void PlayerTick(float DeltaTime) override;	// MoveToMouseCursor를 실시간으로 호출하기 위한 Tick
};
