#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global.h"
#include "FPSCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "ATrap.generated.h"

UCLASS()
class P2022_API AATrap : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* TrapMeshBody;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* TrapMesh1;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* TrapMesh2;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* BoxCollision;

	bool IsOverlap;
	AFPSCharacter* player;

protected:
	virtual void BeginPlay() override;
	
public:	
	AATrap();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
