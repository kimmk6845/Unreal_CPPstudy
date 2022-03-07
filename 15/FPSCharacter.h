#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Global.h"
// 컴포넌트
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
// 위젯 + 게임모드
#include "Components/Widget.h"
#include "AdrenalineBuffWidget.h"
//#include "PlayerWidget.h"
#include "CGameModeBase.h"
#include "DamageRecieveWidget.h"
// 파티클
#include "Particles/ParticleSystem.h"
// 아이템
#include "Interactable.h"
#include "PickupItemBase.h"
#include "InventoryWidget.h"

#include "FPSCharacter.generated.h"

UCLASS()
class P2022_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	// 축 매핑
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	void OnLookUp(float Axis);
	void OnTurn(float Axis);

	// 액션매핑
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
	// 변수
	ACGameModeBase* gamemode;
	float PlayerHP;			// 플레이어 기본 체력
	float PlayerStamina;	// 플레이어 스테미너
	bool availableSprint;	// 스테미너에 따른 달리기 가능 여부 체크변수
	bool isFiring;			// 연사를 위한 체크변수
	FTimerHandle timer;		// 딜레이 타이머 변수
	float BaseDamage;		// 플레이어 기본 데미지
	int32 ammo;				// 탄창
	bool IsReloading = false;	// 재장전 체크 변수
	float reach;			// 픽업을 위한 거리
	bool toggleinven = false;	// 인벤토리 위젯 토글 변수
	bool Adrenaline;		// 아드레날린 사용 체크 변수
	float AdTime;			// 아드레날린 적용 시간
	 
public:
	// 생성자
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
		void UpdatePlayerHP(float value) { PlayerHP = PlayerHP + value; }
	UFUNCTION()
		void UpdateAdvanceDamage(float value) { BaseDamage = BaseDamage + value; }
	UFUNCTION()
		void SetPlayerStamina(float value) { PlayerStamina = value; }
	UFUNCTION()
		void UseAdrenaline() { Adrenaline = true; }

	// 인벤토리, 픽업
	void CheckForInteractables();
	AInteractable* currentInteractable;
	// 플레이어 인벤토리
	UPROPERTY(EditAnywhere)
		TArray<APickupItemBase*> Inventory;


protected:
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, class AActor* DamageCauser) override;


public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	// 컴포넌트
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

	// 총알 관련 파티클
	UPROPERTY(EditAnywhere, Category = Effect)
		class UParticleSystem* ShotEffect;
	UPROPERTY(EditAnywhere, Category = Effect)
		class UParticleSystem* ZombieHitEffect;
	UPROPERTY(EditAnywhere, Category = Effect)
		class UParticleSystem* HitEffect;

	// 위젯
	class ACGameModeBase* GMD;
	class UPlayerWidget* PlayerWidget;
	UPROPERTY(EditAnywhere, Category = WidgetClass)
		TSubclassOf<UUserWidget> BloodEffectClass;
	UPROPERTY(VisibleInstanceOnly)
		class UDamageRecieveWidget* BloodEffectWidget;
	UPROPERTY(EditAnywhere, Category = "invenWidget")
		TSubclassOf<UUserWidget> invenClass;
	class UInventoryWidget* InventoryWidget;
	UPROPERTY(EditAnywhere, Category = "BuffWidget")
		TSubclassOf<UUserWidget> BuffClass;
	class UAdrenalineBuffWidget* AdrenalineWidget;


	// 아이템 관련
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
	UFUNCTION()
		void AdrenalineBuffOn();
	UFUNCTION()
		void AdrenalineBuffOff();
};
