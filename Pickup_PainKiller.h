#pragma once

#include "CoreMinimal.h"
#include "My/PickupItemBase.h"
#include "Pickup_PainKiller.generated.h"

UCLASS()
class P2022_API APickup_PainKiller : public APickupItemBase
{
	GENERATED_BODY()

private:
	float Stamina;

public:
	APickup_PainKiller();

	virtual void Use_Implementation() override;
	
};
