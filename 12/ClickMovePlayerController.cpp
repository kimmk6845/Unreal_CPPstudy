// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickMovePlayerController.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>

AClickMovePlayerController::AClickMovePlayerController()
{
	bShowMouseCursor = true;	// 마우스 커서를 보여줌
}

void AClickMovePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &AClickMovePlayerController::InputLeftMouseButtonPressed);
	InputComponent->BindAction("LeftClick", IE_Released, this, &AClickMovePlayerController::InputLeftMouseButtonReleased);
}

void AClickMovePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bClickLeftMouse)
	{
		MoveToMouseCursor();
	}

}

void AClickMovePlayerController::InputLeftMouseButtonPressed()
{
	bClickLeftMouse = true;
}

void AClickMovePlayerController::InputLeftMouseButtonReleased()
{
	bClickLeftMouse = false;
}

void AClickMovePlayerController::SetNewDestination(const FVector Destination)
{
	APawn* const MyPawn = GetPawn();

	if (MyPawn)
	{
		float const Distance = FVector::Dist(Destination, MyPawn->GetActorLocation());
		if (Distance > 120.0f)
		{
			// 클릭한 위치로 이동시키는 함수 (AI Module의 내장 함수)
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Destination);
		}
	}
}

void AClickMovePlayerController::MoveToMouseCursor()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);	// 마우스 커서 아래에 레이트레이스를 쏨

	// 그 위치를 SetNewDestination 함수에 전달하기
	if (Hit.bBlockingHit)
	{
		SetNewDestination(Hit.ImpactPoint);
	}
}