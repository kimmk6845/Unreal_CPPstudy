// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Engine/Classes/Components/TextRenderComponent.h>	// 헤더를 include할 때 generated.h 위에 선언해야 함!!!!
#include "Countdown.generated.h"

UCLASS()
class VARIABLE_TIMER_EVENT_API ACountdown : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACountdown();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// 화면에 숫자를 표시하는 작업

	// 에디터에서 변수 값을 바꿀 수 있도록 함
	UPROPERTY(EditAnywhere)
	int32 CountdownTime;

	UTextRenderComponent* CountdownText;

	void UpdateTimerDisplay();

	// 시간을 체크할 타이머 추가하는 작업
	void AdvanceTimer();	// 타이머가 돌아가면서 호출될 함수

	// 함수를 블루프린트에 공개해 기능을 수정할 수 있도록
	UFUNCTION(BlueprintNativeEvent)
	void CountdownHasFinished(); // AdvanceTimer함수가 타이머가 지정한 만큼 작동한 뒤에 마무리 처리하는 함수
	virtual void CountdownHasFinished_Implementation();

	FTimerHandle CountdownTimerHandle;	// FTimerHandle은 타이머를 컨트롤하기 위한 구조체로 카운트다운이 끝났을때 타이머가 지속해서 돌아가지 않도록 종료하는 변수


};
