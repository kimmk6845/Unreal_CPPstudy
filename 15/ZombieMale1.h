#pragma once

#include "CoreMinimal.h"
#include "My/ZombieBaseCharacter.h"
#include "ZombieMale1.generated.h"

UCLASS()
class P2022_API AZombieMale1 : public AZombieBaseCharacter
{
	GENERATED_BODY()

public:
	AZombieMale1();
	
	virtual void Detect_Implementation() override;
	virtual void DetectOff_Implementation() override;
};
