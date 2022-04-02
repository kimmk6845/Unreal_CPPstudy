#pragma once

#include "ArenaBattle.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "GameFramework/Actor.h"
#include "RotatingMovementActor.generated.h"

UCLASS()
class ARENABATTLE_API ARotatingMovementActor : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
		float RotateSpeed;

protected:
	virtual void BeginPlay() override;

public:	
	ARotatingMovementActor();

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
		URotatingMovementComponent* Movement;

};
