#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "ZombieBaseCharacter.h"
#include "FPSCharacter.h"
#include "ZombieAIController.h"

#include "BTTask_TurnToTarget.generated.h"

UCLASS()
class P2022_API UBTTask_TurnToTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
