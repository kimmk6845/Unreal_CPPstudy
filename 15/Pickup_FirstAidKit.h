#pragma once

#include "CoreMinimal.h"
#include "My/PickupItemBase.h"
#include "Pickup_FirstAidKit.generated.h"

UCLASS()
class P2022_API APickup_FirstAidKit : public APickupItemBase
{
	GENERATED_BODY()

private:
	float healing;
	
public:
	APickup_FirstAidKit();

	virtual void Use_Implementation() override;
};
