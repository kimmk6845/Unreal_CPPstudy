#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "C_AIController.generated.h"

UCLASS(config=Game)
class FPS_BEGIN_API AC_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AC_AIController(FObjectInitializer const& object_initializer=FObjectInitializer::Get());

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* pawn) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual FRotator GetControlRotation() const override;

	UFUNCTION(BlueprintCallable, Category = "Behavior")
		void on_target_detected(AActor* actor, FAIStimulus const stimulus);

	class UBlackboardComponent* get_blackboard() const;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "AI")
	float AISightRadius = 1500.0f;	// 시야 반경

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "AI")
	float AISightAge = 5.0f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "AI")
	float AILoseSightRadius = AISightRadius + 50.0f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "AI")
	float AIFieldOfView = 100.0f;	// 시야각

private:
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* behavior_tree_comp;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* btree;

	class UAISenseConfig_Sight* SightConfig;
	class UAIPerceptionComponent* Perceptions;
	class UBlackboardComponent* blackboard;	

	void setup_perception_system();
};
