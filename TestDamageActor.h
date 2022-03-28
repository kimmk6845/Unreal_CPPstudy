#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestDamageActor.generated.h"

UCLASS()
class P2022_API ATestDamageActor : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* BoxCollision;
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;
	
public:	
	ATestDamageActor();

	UPROPERTY(EditAnywhere)
		float Damage;
	
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
