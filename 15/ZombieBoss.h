#pragma once

#include "CoreMinimal.h"
#include "My/ZombieBaseCharacter.h"
#include "ZombieBoss.generated.h"

UCLASS()
class P2022_API AZombieBoss : public AZombieBaseCharacter
{
	GENERATED_BODY()
	
public:
	AZombieBoss();

	virtual void Detect_Implementation() override;
	virtual void DetectOff_Implementation() override;
};
