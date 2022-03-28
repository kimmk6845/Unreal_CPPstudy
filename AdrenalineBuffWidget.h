#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "AdrenalineBuffWidget.generated.h"

UCLASS()
class P2022_API UAdrenalineBuffWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
		class UImage* BuffOverlay;

public:
	virtual void NativeConstruct() override;
};
