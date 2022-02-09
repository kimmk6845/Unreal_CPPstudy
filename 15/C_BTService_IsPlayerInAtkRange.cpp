#include "C_BTService_IsPlayerInAtkRange.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "C_AIController.h"
#include "C_ZombieCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "blackboard_keys.h"
#include "Global.h"

UC_BTService_IsPlayerInAtkRange::UC_BTService_IsPlayerInAtkRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player in Attack Range");
}

void UC_BTService_IsPlayerInAtkRange::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::OnBecomeRelevant(owner_comp, node_memory);

	AC_AIController* const cont = Cast<AC_AIController>(owner_comp.GetAIOwner());
	AC_ZombieCharacter* const Bot = Cast<AC_ZombieCharacter>(cont->GetPawn());

	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	cont->get_blackboard()->SetValueAsBool(bb_keys::player_is_in_AttackRange, Bot->GetDistanceTo(player) <= Attack_range);
}
