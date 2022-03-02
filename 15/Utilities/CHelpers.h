#pragma once
#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"

class P2022_API CHelpers
{
public:
	// �ּ� ����
	// �����ڿ����� ��밡��(ConstructorHelpers)
	template<typename T>
	static void GetAsset(T** OutObject, FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), TEXT("asset.Succeeded()"));

		*OutObject = asset.Object;
	}

	// ���� �ε�
	template<typename T>
	static void GetAssetDynamic(T** OutObject, FString InPath)
	{
		T* obj = Cast<T>(StaticLoadObject(T::StaticClass(), NULL, *InPath));
		verifyf(!!obj, TEXT("!!asset"));

		*OutObject = obj;
	}

	// ������Ʈ ����
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

	// �������Ʈ Ŭ���� �ε�
	template<typename T>
	static void GetClass(TSubclassOf<T>* OutClass, FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), TEXT("asset.Succeeded()"));

		*OutClass = asset.Class;
	}
};