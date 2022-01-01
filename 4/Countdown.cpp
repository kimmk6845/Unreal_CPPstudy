// Fill out your copyright notice in the Description page of Project Settings.


#include "Countdown.h"

// Sets default values
ACountdown::ACountdown()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;	// Tick Disable

	CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Countdown Text"));
	CountdownText->SetHorizontalAlignment(EHTA_Center);		// 랜더링 텍스트 가운데 정렬
	CountdownText->SetWorldSize(150.0f);
	RootComponent = CountdownText;	// 루트 컴포넌트로 만들어줌
	CountdownTime = 3;
}

// Called when the game starts or when spawned
void ACountdown::BeginPlay()
{
	Super::BeginPlay();
	
	UpdateTimerDisplay(); // 생성자에서 초기화된 CountdownTime을 출력

	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACountdown::AdvanceTimer, 1.0f, true);	// 타이머 실행

}

void ACountdown::UpdateTimerDisplay()
{
	// 변수를 이용해 화면에 숫자를 표시
	CountdownText->SetText(FString::FromInt(FMath::Max(CountdownTime, 0)));
}

void ACountdown::AdvanceTimer()
{
	--CountdownTime;
	UpdateTimerDisplay(); // 텍스트 업데이트

	if (CountdownTime < 1)	// 카운트다운이 0이 되면,
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle); // 타이머 멈춤
		CountdownHasFinished();
	}
}

void ACountdown::CountdownHasFinished_Implementation()
{
	CountdownText->SetText(TEXT("Go!"));
}
