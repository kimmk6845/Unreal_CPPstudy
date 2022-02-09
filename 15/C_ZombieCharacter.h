#pragma once

#include "CoreMinimal.h"
#include "C_BasicCharacter.h"
#include "Animation/AnimMontage.h"
#include "CombatInterface.h"
#include "C_ZombieCharacter.generated.h"

UCLASS()
class FPS_BEGIN_API AC_ZombieCharacter : public AC_BasicCharacter, public ICombatInterface
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AC_ZombieCharacter();

	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Health;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MaxHealth;
	

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, class AActor* DamageCauser) override;
	void Die();

	/////

	UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree* BotBehavior;

	virtual int melee_attack_Implementation()override;

	UAnimMontage* get_montage() const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* montage;

};
