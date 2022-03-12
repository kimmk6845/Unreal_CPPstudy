#include "BTTaskNode_Attack.h"

UBTTaskNode_Attack::UBTTaskNode_Attack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	//auto Zombie = Cast<AZombieBaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	//if (nullptr == Zombie)
	//	return EBTNodeResult::Failed;

	//Zombie->Attack();
	//IsAttacking = true;
	//Zombie->OnAttackEnd.AddLambda([this]() -> void {
	//	IsAttacking = false;
	//	});

	return EBTNodeResult::InProgress;	// 애니메이션이 끝나는동안 대기
}

void UBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	//if (!IsAttacking)
	//{
	//	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//}
}
