#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "InventoryWidget.generated.h"

UCLASS()
class P2022_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
		class UButton* Btn0;
	UPROPERTY(meta = (BindWidget))
		class UButton* Btn1;
	UPROPERTY(meta = (BindWidget))
		class UButton* Btn2;
	UPROPERTY(meta = (BindWidget))
		class UButton* Btn3;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ItemText0;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ItemText1;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ItemText2;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ItemText3;

public:
	virtual void NativeConstruct() override;
};
