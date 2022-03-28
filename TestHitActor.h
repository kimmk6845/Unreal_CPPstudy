#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestHitActor.generated.h"

UCLASS()
class P2022_API ATestHitActor : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
		float hp;

public:	
	ATestHitActor();

protected:
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, class AActor* DamageCauser) override;

public:
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* mesh;

	void Die();
};
