#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "FPSCharacter.h"
#include "Global.h"

#include "PickupItemBase.generated.h"

UCLASS()
class P2022_API APickupItemBase : public AInteractable
{
	GENERATED_BODY()
	
public:
	APickupItemBase();

	virtual void BeginPlay() override;

	virtual void Interact_Implementation() override;	// ��ȣ�ۿ� �Լ�

	UFUNCTION(BlueprintNativeEvent)
		void Use();
	virtual void Use_Implementation();	// ������ ��� �Լ�




	UPROPERTY(EditAnywhere, Category = "Interact Properties")
		UTexture2D* pickupThumbnail;

	UPROPERTY(EditAnywhere, Category = "Interact Properties")
		FString itemName;

	void OnPickUp();	// �������� �ֿ� �� ȣ��
};
