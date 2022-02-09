#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "C_FPSProjectile.generated.h"

UCLASS()
class FPS_BEGIN_API AC_FPSProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_FPSProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Projectile")
		USphereComponent* CollisionComponent;	// 충돌 처리

	UPROPERTY(VisibleAnywhere, Category = "Movement")
		UProjectileMovementComponent* ProjectileMovementComponent;	// 움직임 처리

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Mesh;		// 총알 메시

	void FireInDirection(const FVector& ShootDirection);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NotmalImpulse, const FHitResult& Hit);

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;


private:
	UPROPERTY(EditAnywhere)
		class USoundCue* shot;

};
