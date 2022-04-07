#pragma once

#include "ArenaBattle.h"
#include "Animation/AnimInstance.h"
#include "ABAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);

UCLASS()
class ARENABATTLE_API UABAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Pawn", meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Pawn", meta = (AllowPrivateAccess = true))
		bool IsInAir;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Attack", meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage;



	UFUNCTION()
		void AnimNotify_AttackHitCheck();	// Attack 몽타주에 넣은 노티파이
	UFUNCTION()
		void AnimNotify_NextAttackCheck();	// 콤보가 가능한지 확인하는 노티파이

	FName GetAttackMontageSectionName(int32 Section);

public:
	UABAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayAttackMontage();
	void JumpToAttackMontageSection(int32 NewSection);

	// 델리게이트 함수
	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	
};
