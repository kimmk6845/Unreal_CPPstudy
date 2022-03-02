#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "FPSCharacter.generated.h"

UCLASS()
class P2022_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	// �� ����
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	void OnLookUp(float Axis);
	void OnTurn(float Axis);

	// �׼Ǹ���
	void OnRunning();
	void OffRunning();
	void OnFire();
	void OffFire();
	void Reloading();
	
	UFUNCTION(BlueprintCallable)
		void Fire();

private:
	// ����
	float PlayerHP;
	float PlayerStamina;
	bool availableSprint;
	bool isFiring;
	FTimerHandle timer;
	float BaseDamage;
	int32 ammo;		// źâ
	bool IsReloading = false;

	 
public:
	// ������
	AFPSCharacter();

	// Getter
	UFUNCTION(BlueprintCallable)
		int32 GetAmmo() { return ammo; }
	UFUNCTION(BlueprintCallable)
		float GetPlayerHP() { return PlayerHP; }
	UFUNCTION(BlueprintCallable)
		float GetPlayerStamina() { return PlayerStamina; }
	UFUNCTION(BlueprintCallable)
		bool GetAvailableSprint() { return availableSprint; }

protected:
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, class AActor* DamageCauser) override;


public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	// ������Ʈ
	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* camera;
	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* Mesh1p;
	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* FPSGun;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* EmptyAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* ReloadSound;

	// �Ѿ� ���� ��ƼŬ
	UPROPERTY(EditAnywhere, Category = Effect)
		class UParticleSystem* ShotEffect;
	UPROPERTY(EditAnywhere, Category = Effect)
		class UParticleSystem* ZombieHitEffect;
	UPROPERTY(EditAnywhere, Category = Effect)
		class UParticleSystem* HitEffect;

	// ����
	class ACGameModeBase* GMD;
	class UPlayerWidget* PlayerWidget;
	UPROPERTY(EditAnywhere, Category = WidgetClass)
		TSubclassOf<UUserWidget> BloodEffectClass;
	UPROPERTY(VisibleInstanceOnly)
		class UDamageRecieveWidget* BloodEffectWidget;
};
