#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "MissionWidget.generated.h"

UCLASS()
class P2022_API UMissionWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
		class UTextBlock* missionText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
		class UTextBlock* infoText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
		class UTextBlock* TurretText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
		class UTextBlock* bindText;

public:
	virtual void NativeConstruct() override;

	void SetMissionText(int32 turretNum);
};
