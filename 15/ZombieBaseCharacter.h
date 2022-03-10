#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZombieAIController.h"
#include "ZombieBaseCharacter.generated.h"

UCLASS()
class P2022_API AZombieBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AZombieBaseCharacter();

protected:
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, class AActor* DamageCauser) override;
	

	UPROPERTY(EditAnywhere, Category = "info")		
		FName zombieType;
	UPROPERTY(EditAnywhere, Category = "info")
		float baseHp;
	UPROPERTY(EditAnywhere, Category = "info")
		float zombieDamage;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Die();

	UFUNCTION(BlueprintCallable)
	float GetHp() { return baseHp; }

};
