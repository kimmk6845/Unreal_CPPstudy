#include "ZombieBaseCharacter.h"

AZombieBaseCharacter::AZombieBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	Tags.Add("Zombie");
	IsAttacking = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// AI컨트롤 클래스 부여
	CHelpers::GetClass<AController>(&AIControllerClass, "Blueprint'/Game/_My/Blueprints/Zombie/BP_ZombieAIController'");
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	// AIControllerClass = AZombieAIController::StaticClass();	// C 클래스
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
		this->GetController()->UnPossess();		// 컨트롤러 연결 끊음
		GetCharacterMovement()->SetMovementMode(MOVE_None);

		// delay (죽는 애니메이션)
		FTimerHandle WaitHandle;
		float WaitTime = 2.5f;	//시간 설정
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
			{
				Die();
			}), WaitTime, false); // true이면 반복
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
	float WaitTime = 1.5f;	// 애니메이션 실행시간
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

