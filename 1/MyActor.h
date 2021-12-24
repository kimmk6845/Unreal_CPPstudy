// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class CPP_TUTORIAL_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();


	// ���� �����
	UPROPERTY()
	int32 IntVariable;

	//// �÷������� ���̰� �޶��� �� ����
	//short s;
	//int i;
	//long l;
	
	// �������� ���
	int8 i8;	// 127 ~ -128
	int16 i16; 
	int32 i32;
	int64 i64;

	// ����� ���
	uint8 ui8;	// 0 ~ 255
	uint16 ui16;
	uint32 ui32;
	uint64 ui64;
	


	// �ε��Ҽ���
	float f;
	double d;

	// ���ڿ�
	FString str;	// ��������
	
	// ������
	bool b;

public:
	// ��� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	int32 TotalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageTimeInSeconds;

	// �������Ʈ���� �б⸸ ����, ������Ƽ�� ��� ������Ƽâ���� �������� ���� �Ұ�, �ֹ߼� ������Ƽ�� ������� ����
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Transient,Category = "Damage")
	float DamagePerSecond;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAttackable;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	//// Tick �Լ��� ������� ������ ���������ν� �����ս��� ����Ű��
	//// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
