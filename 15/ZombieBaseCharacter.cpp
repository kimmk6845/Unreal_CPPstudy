#include "ZombieBaseCharacter.h"

AZombieBaseCharacter::AZombieBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	Tags.Add("Zombie");

	// AI��Ʈ�� Ŭ���� �ο�
	AIControllerClass = AZombieAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AZombieBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

float AZombieBaseCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float GetDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	baseHp -= GetDamage;
	UE_LOG(LogTemp, Log, TEXT("Actor baseHp : %f, Actor Name: %s"), baseHp, *zombieType.ToString());

	if (baseHp <= 0.0f)
	{
		GetMesh()->SetCollisionProfileName("NoCollision");

		// delay (�״� �ִϸ��̼�)
		FTimerHandle WaitHandle;
		float WaitTime = 2.5f;	//�ð� ����
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
			{
				Die();
			}), WaitTime, false); // true�̸� �ݺ�
	}

	return 0.0f;
}

void AZombieBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZombieBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AZombieBaseCharacter::Die()
{
	this->Destroy();
}