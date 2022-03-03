#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Global.h"
// ������Ʈ
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
// ���� + ���Ӹ��
#include "Components/Widget.h"
//#include "PlayerWidget.h"
#include "CGameModeBase.h"
#include "DamageRecieveWidget.h"
// ��ƼŬ
#include "Particles/ParticleSystem.h"
// ������
#include "Interactable.h"
#include "PickupItemBase.h"
#include "InventoryWidget.h"

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
	
	void ToggleInventory();
	void Interact();

	UFUNCTION(BlueprintCallable)
		void Fire();

private:
	// ����
	float PlayerHP;			// �÷��̾� �⺻ ü��
	float PlayerStamina;	// �÷��̾� ���׹̳�
	bool availableSprint;	// ���׹̳ʿ� ���� �޸��� ���� ���� üũ����
	bool isFiring;			// ���縦 ���� üũ����
	FTimerHandle timer;		// Ÿ�̸� ����
	float BaseDamage;		// �÷��̾� �⺻ ������
	int32 ammo;				// źâ
	bool IsReloading = false;	// ������ üũ ����
	float reach;			// �Ⱦ��� ���� �Ÿ�
	bool toggleinven = false;	// �κ��丮 ���� ��� ����

	 
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

	// Setter
	UFUNCTION()
		void SetPlayerHP(float value) { PlayerHP = PlayerHP + value; }
	UFUNCTION()
		void SetAdvanceDamage(float value) { BaseDamage = BaseDamage + value; }

	// �κ��丮, �Ⱦ�
	void CheckForInteractables();
	AInteractable* currentInteractable;
	// �÷��̾� �κ��丮
	UPROPERTY(EditAnywhere)
		TArray<APickupItemBase*> Inventory;


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
	UPROPERTY(EditAnywhere, Category = "inven")
		TSubclassOf<UUserWidget> invenClass;
	class UInventoryWidget* InventoryWidget;

	// ������ ����
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HUD")
		FString helpText;
	UFUNCTION(BlueprintPure, Category = "Inventory Functions")
		bool AddItemToInventory(APickupItemBase* item);
	UFUNCTION(BlueprintPure, Category = "Inventory Functions")
		UTexture2D* GetTumbnailAtInventorySlot(int32 Slot);
	UFUNCTION(BlueprintPure, Category = "Inventory Functions")
		FString GetItemNameAtInventorySlot(int32 Slot);
	UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
		void UseItemAtInventorySlot(int32 Slot);
};
