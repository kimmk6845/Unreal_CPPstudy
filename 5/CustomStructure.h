// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomStructure.generated.h"

/**
 * 
 */
class STRUCTURE_API CustomStructure
{
public:
	CustomStructure();
	~CustomStructure();
};

// Atomic�� ����ü�� �׻� �ϳ��� ������ ����ȭ
// BlueprintType�� ����ü�� �������Ʈ���� ���� �� ����

USTRUCT(Atomic,BlueprintType)
struct FCustomStruct
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	// ��۸������� ������ ��ȣ�ޱ� ����
	AActor* actor;	// �����͸� ����ϸ� ���� ����� ���� ���� ������ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 i;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float f;
};

// ����ü�� �������� ������ â�� ǥ�õǰ� ���� �����ϱ⸸ ���ϸ� USTRUCT �����ڸ� Atomic���� �����ϰ�
// ��������� �����ڸ� EditAnywhere�� ������

// �ݴ��, ������ â���� ������ �ʰ� �ڵ� ���γ� �������Ʈ������ ���Ǵ� ���� ���ϸ� BlueprintType���� �����ϰ�
// ��������� BlueprintReadWrite�θ� ����