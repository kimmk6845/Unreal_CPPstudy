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


	// �����̳ʰ� ���� �������Ʈ�� C++���� ����� �� �ֵ��� �ϴ� ����
	// UFUNCTION���� BlueprintImplementableEvent ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	FString str;

	/*
	UFUNCTION(BlueprintImplementableEvent, Category = "Damage")
	void CallFromCPP();	// ����� �����̳ʰ� ����� ������ �Լ� �ٵ� ���� �ʿ䰡 ����!!
	*/

	// BlueprintImplementableEvent�� �������Ʈ�� ���� ����� ���α׷��Ӱ� ���ϴ� C++ �ڵ忡�� ȣ���ϴ� �����
	// BlueprintNativeEvent �����ڴ� �����̳ʰ� �������Ʈ�� ����� ���� �� �ְ� �ϸ鼭��
	// �����̳ʰ� �������� ������ ���α׷��Ӱ� C++���� ������ �� ����
	UFUNCTION(BlueprintNativeEvent, Category = "Damage")
	void CallFromCPP();
	virtual void CallFromCpp_Implementation();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// UFUNCTION ����ϱ�
	void FunctionName();

	UFUNCTION(BlueprintCallable,Category = "Damage") // �Լ��� �������Ʈ���� ����� �� ���� (BlueprintCallable), ī�װ��� �Ҵ������ �������Ʈ���� �����۵�
	void CalculateDPS();

	// AmyActor�� �θ�Ŭ������ AActor���� ��ӹ޴� �Լ�
	// ������Ƽ�� �ʱ�ȭ�� �� ȣ��Ǵ� �Լ�
	virtual void PostInitProperties() override;

	// ������Ƽ�� ������ �� ȣ��Ǵ� �Լ�
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
