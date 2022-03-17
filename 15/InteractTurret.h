#pragma once

#include "CoreMinimal.h"
#include "My/Interactable.h"
#include "Global.h"
#include "FPSCharacter.h"
#include "Components/PointLightComponent.h"
#include "Components/WidgetComponent.h"
#include "TurretWidget.h"

#include "InteractTurret.generated.h"

UCLASS()
class P2022_API AInteractTurret : public AInteractable
{
	GENERATED_BODY()

private:
	float occupyPercent;
	bool IsOccupying;
	AFPSCharacter* player;
	int32 cnt;
	
public:
	AInteractTurret();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation() override;

	virtual void InteractOff_Implementation() override;

	UPROPERTY(VisibleAnywhere)		
		class UStaticMeshComponent* TurretTopMesh;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* TurretBottomMesh;
	UPROPERTY(VisibleAnywhere)
		class UPointLightComponent* Light;
	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* widget;
	class UTurretWidget* TurretWidget;

	float GetOccupyPercent() { return occupyPercent; }

	UFUNCTION()
		void Succeed();
};
