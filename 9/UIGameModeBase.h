// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UIGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UI_API AUIGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable,Category = "UMG_Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	virtual void BeginPlay() override;

	// 게임이 시작될 때 표시될 UI 위젯을 저장
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "UMG_Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	// 현재 화면에 표시되고 있는 UI 위젯을 저장
	UPROPERTY()
	UUserWidget* CurrentWidget;
};
