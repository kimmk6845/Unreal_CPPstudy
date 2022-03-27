#include "BTService_Detect.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
	detectRange = 600.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();
	if (nullptr == World) return;

	FVector Center = ControllingPawn->GetActorLocation();
	// ���� ����
	float DetectRadius = detectRange;

	// ���� ���·� �÷��̾� ������
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4,	// �÷��̾ ������ �� �ִ� ä��
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	if (bResult)
	{
		// ������ ���Ͱ� �÷��̾����� �˻�
		for (FOverlapResult OverlapResult : OverlapResults)
		{
			AFPSCharacter* character = Cast<AFPSCharacter>(OverlapResult.GetActor());
			AZombieBaseCharacter* zombie = Cast<AZombieBaseCharacter>(ControllingPawn);
			if (character && character->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AZombieAIController::TargetKey, character);

				if (zombie != nullptr)
				{
					zombie->Detect_Implementation();
				}
				//DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				return;
			}
			else
			{
				if (zombie != nullptr)
				{
					zombie->DetectOff_Implementation();
				}
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AZombieAIController::TargetKey, nullptr);
			}
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AZombieAIController::TargetKey, nullptr);
	}
	//DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}
