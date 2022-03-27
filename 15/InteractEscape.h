#pragma once

#include "CoreMinimal.h"
#include "My/Interactable.h"
#include "Global.h"
#include "FPSCharacter.h"

#include "InteractEscape.generated.h"

UCLASS()
class P2022_API AInteractEscape : public AInteractable
{
	GENERATED_BODY()

public:
	AInteractEscape();

	virtual void Interact_Implementation() override;
};
