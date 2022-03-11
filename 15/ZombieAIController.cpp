#include "ZombieAIController.h"

const FName AZombieAIController::HomePosKey(TEXT("HomePos"));
const FName AZombieAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AZombieAIController::TargetKey(TEXT("Target"));

AZombieAIController::AZombieAIController()
{
	CHelpers::GetAsset<UBlackboardData>(&BBZombie, "BlackboardData'/Game/_My/Blueprints/Zombie/BB_Zombie.BB_Zombie'");
	CHelpers::GetAsset<UBehaviorTree>(&BTZombie, "BehaviorTree'/Game/_My/Blueprints/Zombie/BT_Zombie.BT_Zombie'");

}

void AZombieAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunAI();

	/*if (UseBlackboard(BBZombie, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
	}*/
}


void AZombieAIController::RunAI()
{
	if (UseBlackboard(BBZombie, Blackboard))
	{
		RunBehaviorTree(BTZombie);	
	}
}

void AZombieAIController::StopAI()
{
	UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComp == nullptr)
		return;

	BTComp->StopTree(EBTStopMode::Safe);
}