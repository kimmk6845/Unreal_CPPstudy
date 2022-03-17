#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZombieAIController.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "FPSCharacter.h"

#include "ZombieBaseCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);
UCLASS()
class P2022_API AZombieBaseCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	bool IsAttacking;
	bool IsOverlap;
	AActor* overlapActor;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* attackBox;

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
	AZombieBaseCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Die();
	void Attack();

	FOnAttackEndDelegate OnAttackEnd;
	UFUNCTION()
		void OnAttackEnded();

	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
		void OnHit();

	virtual void Detect_Implementation();
	virtual void DetectOff_Implementation();

	UFUNCTION(BlueprintCallable)
	float GetHp() { return baseHp; }
	UFUNCTION(BlueprintCallable)
	bool GetAttack() { return IsAttacking; }
};
