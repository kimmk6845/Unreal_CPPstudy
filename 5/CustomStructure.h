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

// Atomic은 구조체가 항상 하나의 단위로 직렬화
// BlueprintType은 구조체가 블루프린트에서 사용될 수 있음

USTRUCT(Atomic,BlueprintType)
struct FCustomStruct
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	// 댕글링포인터 문제에 보호받기 위함
	AActor* actor;	// 포인터를 사용하면 깊은 복사와 얕은 복사 문제에 주의
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 i;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float f;
};

// 구조체가 에디터의 디테일 창에 표시되고 수정 가능하기만 원하면 USTRUCT 지정자를 Atomic으로 설정하고
// 멤버변수의 지정자를 EditAnywhere로 설정함

// 반대로, 디테일 창에서 보이지 않고 코드 내부나 블루프린트에서만 사용되는 것을 원하면 BlueprintType으로 설정하고
// 멤버변수는 BlueprintReadWrite로만 설정