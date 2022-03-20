#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Global.h"

#include "MenuWidget.generated.h"

UCLASS()
class P2022_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* btnStart;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* btnExit;

public:
	virtual void NativeConstruct() override;
	
	void GameStartClick();

	void ExitClick();
};
