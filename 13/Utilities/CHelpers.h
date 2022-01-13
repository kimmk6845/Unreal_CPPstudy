#pragma once

#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"

class UONLINE_CPP_API CHelpers
{
public:
	// GetAsset�� �����ڿ����� ����� �� ���� ==> ConstructorHelpers�� ����ϱ� ����!!!!!!!!
	template<typename T>
	static void GetAsset(T** OutObject, FString InPath)
	{
		// FString�� *�� ���̸� ���ڿ� ��� L�̳� TEXT�� ��ȯ�� --> �׷��� InPath�տ� * ���̴� ��
		ConstructorHelpers::FObjectFinder<T> asset(*InPath);	// TEXT�� �����ڵ� L�� ��Ƽ����Ʈ (unreal�� TEXT�� ���°��� ����)
		verifyf(asset.Succeeded(), L"asset.Succeeded()");

		*OutObject = asset.Object;
	}


	// ���� �ε�
	template<typename T>
	static void GetAssetDynamic(T** OutObject, FString InPath)
	{
		T* obj = Cast<T>(StaticLoadObject(T::StaticClass(), NULL, *InPath));
		verifyf(!!obj, L"!!asset");		// !!�� obj != NULL�� ���� �ǹ�, ���н� ������ ���ڿ� = !!asset

		*OutObject = obj;
	}
};