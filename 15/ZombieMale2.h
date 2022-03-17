#pragma once

#include "CoreMinimal.h"
#include "My/ZombieBaseCharacter.h"
#include "ZombieMale2.generated.h"

UCLASS()
class P2022_API AZombieMale2 : public AZombieBaseCharacter
{
	GENERATED_BODY()
	
public:
	AZombieMale2();

	virtual void Detect_Implementation() override;
	virtual void DetectOff_Implementation() override;
};
