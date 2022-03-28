#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"

#include "TurretWidget.generated.h"

UCLASS()
class P2022_API UTurretWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
		class UProgressBar* occupyingBar;

public:
	virtual void NativeConstruct() override;

	void SetOccupyBar(float value);
};
