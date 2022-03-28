#pragma once

#include "CoreMinimal.h"
#include "My/Interactable.h"
#include "Global.h"
#include "DestructibleComponent.h"

#include "InteractBox.generated.h"

UCLASS()
class P2022_API AInteractBox : public AInteractable
{
	GENERATED_BODY()
	
private:
	float BoxHP;

public:
	AInteractBox();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, class AActor* DamageCauser) override;

	virtual void Interact_Implementation() override;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* BoxBody;

	UPROPERTY(EditAnywhere)
		class UDestructibleComponent* Boxdebris;
};
