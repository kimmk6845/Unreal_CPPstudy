#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "PlayerWidget.generated.h"

UCLASS()
class P2022_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* hp;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* hpBar;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* remainAmmo;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* totalAmmo;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* staminaBar;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* pickupText;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* missionText;	// 터렛 숫자 표기
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* infoText;		// 미션 내용

public:
	UPlayerWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	void SetHP(float health);
	void SetHPBar(float health);
	void SetRemainAmmo(int32 ammo);
	void SetStamina(float stamina);
	void SetHelpText(FString text);
	void SetMissionText(int32 turretNum);
	void SetInfoText(FString text);
};
