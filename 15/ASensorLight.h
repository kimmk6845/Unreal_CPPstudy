#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"

#include "ASensorLight.generated.h"

UCLASS()
class P2022_API AASensorLight : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* BoxCollision;
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* SensorLamp;
	UPROPERTY(VisibleDefaultsOnly)
		class UPointLightComponent* PointLight;

	bool bDelayToggle;
	float WaitTime;


protected:
	virtual void BeginPlay() override;

public:	
	AASensorLight();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void ComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
