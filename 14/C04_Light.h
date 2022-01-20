#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C04_Light.generated.h"

UCLASS()
class UONLINE_CPP_API AC04_Light : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

	UPROPERTY(VisibleDefaultsOnly)
		class UPointLightComponent* Light;

public:	
	AC04_Light();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnLight();

	UFUNCTION()
		void OffLight();
};
