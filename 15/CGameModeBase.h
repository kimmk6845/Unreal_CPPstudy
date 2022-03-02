#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerWidget.h"
#include "CGameModeBase.generated.h"

UCLASS()
class P2022_API ACGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "WidgetClass")
		TSubclassOf<UUserWidget> StateClass;

	UPROPERTY(VisibleInstanceOnly)
		class UPlayerWidget* StateWidget;


public:
	ACGameModeBase();

	UPlayerWidget* GetPlayerWidget() const;
};
