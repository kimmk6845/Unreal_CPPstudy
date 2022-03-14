#include "ZombieBaseCharacter.h"

AZombieBaseCharacter::AZombieBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	Tags.Add("Zombie");
	IsAttacking = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// AI��Ʈ�� Ŭ���� �ο�
	CHelpers::GetClass<AController>(&AIControllerClass, "Blueprint'/Game/_My/Blueprints/Zombie/BP_ZombieAIController'");
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	// AIControllerClass = AZombieAIController::StaticClass();	// C Ŭ����
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
		this->GetController()->UnPossess();		// ��Ʈ�ѷ� ���� ����
		GetCharacterMovement()->SetMovementMode(MOVE_None);

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


void AZombieBaseCharacter::Attack()
{
	IsAttacking = true;
	FTimerHandle WaitHandle;
	float WaitTime = 1.5f;	// �ִϸ��̼� ����ð�
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			OnAttackEnded();
		}), WaitTime, false);
}

void AZombieBaseCharacter::OnAttackEnded()
{
	IsAttacking = false;

	OnAttackEnd.Broadcast();
}

