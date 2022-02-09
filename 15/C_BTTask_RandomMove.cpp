#include "C_BTTask_RandomMove.h"
#include "FPS_Begin.h"
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "NavigationSystem.h"
#include "C_AIController.h"
#include "Engine.h"
#include "Engine/World.h"
#include "blackboard_keys.h"

UC_BTTask_RandomMove::UC_BTTask_RandomMove(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Ranfom Location");
}

EBTNodeResult::Type UC_BTTask_RandomMove::ExecuteTask(UBehaviorTreeComponent& owner_Comp, uint8* NodeMemory)
{
	auto const cont = Cast<AC_AIController>(owner_Comp.GetAIOwner());
	auto const npc = cont->GetPawn();
	FVector const origin = npc->GetActorLocation();

	FNavLocation loc;
	UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (nav_sys->GetRandomPointInNavigableRadius(origin, search_radius, loc, nullptr))
	{
		cont->get_blackboard()->SetValueAsVector(bb_keys::target_location, loc.Location);
	}

	FinishLatentTask(owner_Comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
	