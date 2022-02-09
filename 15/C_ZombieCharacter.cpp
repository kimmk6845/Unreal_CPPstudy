#include "C_ZombieCharacter.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

AC_ZombieCharacter::AC_ZombieCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	MaxHealth = 1000;
	Health = MaxHealth;

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88.0f));
	GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));
	GetCharacterMovement()->MaxWalkSpeed = 100.0f;	// 기본 걷기 속도 --> 추격시 500
	Tags.Add("Enemy");

	CHelpers::GetClass<AController>(&AIControllerClass, "Blueprint'/Game/AI/BP_C_AIController.BP_C_AIController_C'");
	GetCharacterMovement()->bOrientRotationToMovement = true;

}

void AC_ZombieCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AC_ZombieCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AC_ZombieCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float GetDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	Health -= GetDamage;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("Zombie HP : %f"), Health));

	if (Health <= 0.0f)
	{
		GetCapsuleComponent()->SetCollisionProfileName("NoCollision");

		// delay
		FTimerHandle WaitHandle;
		float WaitTime = 2.5f;	//시간 설정
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
			{
				Die();
			}), WaitTime, false); // true이면 반복
	}

	return 0.0f;
}

void AC_ZombieCharacter::Die()
{
	this->Destroy();
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Zombie die!!"));
}


int AC_ZombieCharacter::melee_attack_Implementation()
{
	if (montage)
	{
		PlayAnimMontage(montage);
	}
	return 0;
}


UAnimMontage* AC_ZombieCharacter::get_montage() const
{
	return montage;
}