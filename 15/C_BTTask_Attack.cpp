#include "C_BTTask_Attack.h"
#include "C_AIController.h"
#include "Global.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "AIController.h"
#include "C_BasicCharacter.h"
#include "CombatInterface.h"


UC_BTTask_Attack::UC_BTTask_Attack(FObjectInitializer const& object_intializer)
{
	NodeName = TEXT("Melee Attack");
}

EBTNodeResult::Type UC_BTTask_Attack::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AAIController* const cont = owner_comp.GetAIOwner();
	AC_ZombieCharacter* const Bot = Cast<AC_ZombieCharacter>(cont->GetPawn());
	if (ICombatInterface* const icombat = Cast<ICombatInterface>(Bot))
	{
		if (montage_has_finished(Bot))
		{
			icombat->Execute_melee_attack(Bot);
		}
	}
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;

}

bool UC_BTTask_Attack::montage_has_finished(AC_ZombieCharacter* const Bot)
{
	return Bot->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(Bot->get_montage());
}
