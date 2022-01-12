#pragma once

#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"

class UONLINE_CPP_API CHelpers
{
public:
	template<typename T>
	static void GetAsset(T** OutObject, FString InPath)
	{
		// FString의 *를 붙이면 문자열 상수 L이나 TEXT로 반환됨 --> 그래서 InPath앞에 * 붙이는 것
		ConstructorHelpers::FObjectFinder<T> asset(*InPath);	// TEXT는 유니코드 L은 멀티바이트 (unreal은 TEXT를 쓰는것이 정석)
		verifyf(asset.Succeeded(), L"asset.Succeeded()");

		*OutObject = asset.Object;
	}
};