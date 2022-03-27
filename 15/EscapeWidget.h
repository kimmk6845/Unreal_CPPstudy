#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "EscapeWidget.generated.h"

UCLASS()
class P2022_API UEscapeWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
		class UTextBlock* WinText;

public:
	virtual void NativeConstruct() override;
	
};
