// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class UFUNCTION_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Damage")
	int32 TotalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageTimeInSeconds;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Damage")
	float DamagePerSecond;


	// 디자이너가 만든 블루프린트를 C++에서 사용할 수 있도록 하는 것이
	// UFUNCTION에서 BlueprintImplementableEvent 지정자
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	FString str;

	/*
	UFUNCTION(BlueprintImplementableEvent, Category = "Damage")
	void CallFromCPP();	// 기능을 디자이너가 만들기 때문에 함수 바디를 만들 필요가 없음!!
	*/

	// BlueprintImplementableEvent는 블루프린트로 만든 기능을 프로그래머가 원하는 C++ 코드에서 호출하는 방식임
	// BlueprintNativeEvent 지정자는 디자이너가 블루프린트로 기능을 만들 수 있게 하면서도
	// 디자이너가 구현하지 않으면 프로그래머가 C++에서 구현할 수 있음
	UFUNCTION(BlueprintNativeEvent, Category = "Damage")
	void CallFromCPP();
	virtual void CallFromCpp_Implementation();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// UFUNCTION 사용하기
	void FunctionName();

	UFUNCTION(BlueprintCallable,Category = "Damage") // 함수를 블루프린트에서 사용할 수 있음 (BlueprintCallable), 카테고리를 할당해줘야 블루프린트에서 정상작동
	void CalculateDPS();

	// AmyActor의 부모클래스인 AActor에서 상속받는 함수
	// 프로퍼티가 초기화될 때 호출되는 함수
	virtual void PostInitProperties() override;

	// 프로퍼티가 수정될 때 호출되는 함수
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
