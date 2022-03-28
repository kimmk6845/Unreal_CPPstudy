#pragma once

#include "CoreMinimal.h"
#include "My/Interactable.h"
#include "Global.h"

#include "InteractButton.generated.h"

DECLARE_DELEGATE(FTurnOnLight)
DECLARE_DELEGATE(FTurnOffLight)


UCLASS()
class P2022_API AInteractButton : public AInteractable
{
	GENERATED_BODY()

private:
	bool bToggle;
	
public:
	AInteractButton();

	virtual void Interact_Implementation() override;

	// ��������Ʈ�� ALight�� ����
	FTurnOnLight LightOn;
	FTurnOffLight LightOff;
};
