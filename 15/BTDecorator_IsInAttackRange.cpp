#include "BTDecorator_IsInAttackRange.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return false;

	AFPSCharacter* Target = Cast<AFPSCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AZombieAIController::TargetKey));
	if (nullptr == Target) return false;

	bool bResult = (Target->GetDistanceTo(ControllingPawn) <= 200.0f);	// ���ݹ��� 200 �ȿ� ����
	return bResult;
}
