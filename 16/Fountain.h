#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Fountain.generated.h"

UCLASS()
class ARENABATTLE_API AFountain : public AActor
{
	GENERATED_BODY()
	
public:	
	AFountain();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Water;

	UPROPERTY(VisibleAnywhere)
	class UPointLightComponent* Light;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* Splash;

	UPROPERTY(EditAnyWhere, Category = "ID")
		int32 ID;

};
