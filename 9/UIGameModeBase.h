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

	// ������ ���۵� �� ǥ�õ� UI ������ ����
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "UMG_Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	// ���� ȭ�鿡 ǥ�õǰ� �ִ� UI ������ ����
	UPROPERTY()
	UUserWidget* CurrentWidget;
};
