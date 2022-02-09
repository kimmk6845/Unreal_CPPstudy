#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "C_BTService_IsPlayerInAtkRange.generated.h"

UCLASS()
class FPS_BEGIN_API UC_BTService_IsPlayerInAtkRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UC_BTService_IsPlayerInAtkRange();
	void OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		float Attack_range = 30.0f;
};
