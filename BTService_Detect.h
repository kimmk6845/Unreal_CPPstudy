#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"

#include "ZombieAIController.h"
#include "FPSCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "ZombieBaseCharacter.h"

#include "BTService_Detect.generated.h"

UCLASS()
class P2022_API UBTService_Detect : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_Detect();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "AIPerception")
		float detectRange;
};
