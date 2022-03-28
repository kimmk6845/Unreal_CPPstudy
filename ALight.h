#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global.h"
#include "InteractButton.h"
#include "Components/PointLightComponent.h"

#include "ALight.generated.h"

UCLASS()
class P2022_API AALight : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* SceneComp;
	UPROPERTY(VisibleDefaultsOnly)
		class UPointLightComponent* Light;
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Lamp;

protected:
	virtual void BeginPlay() override;

public:	
	AALight();

	UFUNCTION()
		void TurnOn();

	UFUNCTION()
		void TurnOff();

	UPROPERTY(EditAnywhere,Category = "ButtonIndex")
		int32 idx;
};
