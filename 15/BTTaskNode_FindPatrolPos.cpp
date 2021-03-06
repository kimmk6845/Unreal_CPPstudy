#include "BTTaskNode_FindPatrolPos.h"

UBTTaskNode_FindPatrolPos::UBTTaskNode_FindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTaskNode_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return EBTNodeResult::Failed;

	FVector Home = ControllingPawn->GetActorLocation();
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(AZombieAIController::HomePosKey, Home);

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (nullptr == NavSystem) return EBTNodeResult::Failed;

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AZombieAIController::HomePosKey);		// 블랙보드 값 사용
																											//FNavLocation NextPatrol;
	//if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 450.0f, NextPatrol))
	//{
	//	OwnerComp.GetBlackboardComponent()->SetValueAsVector(AZombieAIController::PatrolPosKey, NextPatrol.Location);
	//	return EBTNodeResult::Succeeded;
	//}

	FNavLocation NextPatrol;
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, 450.0f, NextPatrol))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AZombieAIController::PatrolPosKey, NextPatrol.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

