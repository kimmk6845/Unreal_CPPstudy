#pragma once

#include "CoreMinimal.h"
#include "My/ZombieBaseCharacter.h"
#include "ZombieFemale.generated.h"

UCLASS()
class P2022_API AZombieFemale : public AZombieBaseCharacter
{
	GENERATED_BODY()
	
public:
	AZombieFemale();

	virtual void Detect_Implementation() override;
	virtual void DetectOff_Implementation() override;
};
