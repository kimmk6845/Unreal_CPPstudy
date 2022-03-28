#pragma once

#include "CoreMinimal.h"
#include "My/PickupItemBase.h"
#include "Pickup_Pill.generated.h"

UCLASS()
class P2022_API APickup_Pill : public APickupItemBase
{
	GENERATED_BODY()

private:
	float healing;

public:
	APickup_Pill();

	virtual void Use_Implementation() override;
	
};
