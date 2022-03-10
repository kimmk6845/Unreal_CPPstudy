#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Global.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "ZombieAIController.generated.h"

UCLASS()
class P2022_API AZombieAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AZombieAIController();

	UFUNCTION()
		virtual void OnPossess(APawn* InPawn) override;

	void RunAI();
	void StopAI();


	UPROPERTY() 
		class UBlackboardData* BBZombie;
	UPROPERTY() 
		class UBehaviorTree* BTZombie;

	static const FName HomePosKey;		// ���� ��ġ
	static const FName PatrolPosKey;	// �̵��� ��Ʈ�� ��ġ
};
