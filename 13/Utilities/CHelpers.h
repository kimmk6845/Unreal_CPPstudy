#pragma once

#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"

class UONLINE_CPP_API CHelpers
{
public:
	// GetAsset은 생성자에서만 사용할 수 있음 ==> ConstructorHelpers를 사용하기 때문!!!!!!!!
	template<typename T>
	static void GetAsset(T** OutObject, FString InPath)
	{
		// FString에 *를 붙이면 문자열 상수 L이나 TEXT로 반환됨 --> 그래서 InPath앞에 * 붙이는 것
		ConstructorHelpers::FObjectFinder<T> asset(*InPath);	// TEXT는 유니코드 L은 멀티바이트 (unreal은 TEXT를 쓰는것이 정석)
		verifyf(asset.Succeeded(), L"asset.Succeeded()");

		*OutObject = asset.Object;
	}


	// 동적 로딩
	template<typename T>
	static void GetAssetDynamic(T** OutObject, FString InPath)
	{
		T* obj = Cast<T>(StaticLoadObject(T::StaticClass(), NULL, *InPath));
		verifyf(!!obj, L"!!asset");		// !!는 obj != NULL과 같은 의미, 실패시 나오는 문자열 = !!asset

		*OutObject = obj;
	}

	// 컴포넌트 생성
	template<typename T>
	static void CreateComponent(AActor* InActor, T** InComponent, FName InName, USceneComponent* InParent = NULL)
	{
		*InComponent = InActor->CreateDefaultSubobject<T>(InName);

		if (!!InParent)
		{
			(*InComponent)->SetupAttachment(InParent);

			return;
		}

		InActor->SetRootComponent(*InComponent);
	}

	// 블루프린트 클래스 로딩
	template<typename T>
	static void GetClass(TSubclassOf<T>* OutClass, FString InPath)	// TSubclassOf가 기본적으로 포인터, 따라서 OutClass는 2차 포인터인 것과 마찬가지
	{
		ConstructorHelpers::FClassFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), L"asset.Succeeded()");

		*OutClass = asset.Class;
	}

};