#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "ZombieAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

#include "BTTaskNode_FindPatrolPos.generated.h"

UCLASS()
class P2022_API UBTTaskNode_FindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTaskNode_FindPatrolPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
