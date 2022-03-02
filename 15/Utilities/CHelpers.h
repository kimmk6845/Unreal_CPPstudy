#pragma once
#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"

class P2022_API CHelpers
{
public:
	// 애셋 생성
	// 생성자에서만 사용가능(ConstructorHelpers)
	template<typename T>
	static void GetAsset(T** OutObject, FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), TEXT("asset.Succeeded()"));

		*OutObject = asset.Object;
	}

	// 동적 로딩
	template<typename T>
	static void GetAssetDynamic(T** OutObject, FString InPath)
	{
		T* obj = Cast<T>(StaticLoadObject(T::StaticClass(), NULL, *InPath));
		verifyf(!!obj, TEXT("!!asset"));

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
	static void GetClass(TSubclassOf<T>* OutClass, FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), TEXT("asset.Succeeded()"));

		*OutClass = asset.Class;
	}
};