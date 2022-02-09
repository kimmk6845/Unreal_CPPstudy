#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "C_ZombieCharacter.h"
#include "C_BTTask_Attack.generated.h"

UCLASS()
class FPS_BEGIN_API UC_BTTask_Attack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UC_BTTask_Attack(FObjectInitializer const& object_intializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)override;

private:
	bool montage_has_finished(AC_ZombieCharacter* const Bot);
};
