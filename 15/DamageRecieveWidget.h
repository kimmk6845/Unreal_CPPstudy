#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "DamageRecieveWidget.generated.h"

UCLASS()
class P2022_API UDamageRecieveWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UImage* blood;
	
public:
	virtual void NativeConstruct() override;

};
