#pragma once

#include "CoreMinimal.h"
#include "My/PickupItemBase.h"
#include "Pickup_Adrenaline.generated.h"

UCLASS()
class P2022_API APickup_Adrenaline : public APickupItemBase
{
	GENERATED_BODY()

private:
	float advanceDamage;

public:
	APickup_Adrenaline();

	virtual void Use_Implementation() override;
};
