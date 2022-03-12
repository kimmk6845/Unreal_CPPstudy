#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"

#include "ZombieAIController.h"
#include "FPSCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "BTDecorator_IsInAttackRange.generated.h"

UCLASS()
class P2022_API UBTDecorator_IsInAttackRange : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_IsInAttackRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
