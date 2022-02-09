#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSOnHitActor.generated.h"

UCLASS()
class FPS_BEGIN_API AFPSOnHitActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AFPSOnHitActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Health;		// 체력

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float MaxHealth;	// 최대 체력

	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, class AActor* DamageCauser) override;

};
