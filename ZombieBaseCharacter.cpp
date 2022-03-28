#include "ZombieBaseCharacter.h"

AZombieBaseCharacter::AZombieBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	CHelpers::CreateComponent<UBoxComponent>(this, &attackBox, "attackBox", GetCapsuleComponent());
	attackBox->SetRelativeLocation(FVector(41.5f, 0.0f, 0.0f));
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
	
	OnActorBeginOverlap.AddDynamic(this, &AZombieBaseCharacter::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AZombieBaseCharacter::ActorEndOverlap);
}

float AZombieBaseCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float GetDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	baseHp -= GetDamage;
	UE_LOG(LogTemp, Log, TEXT("Actor baseHp : %f, Actor Name: %s"), baseHp, *zombieType.ToString());

	if (baseHp <= 0.0f)
	{
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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

// ���ݾִϸ��̼ǿ� ���缭 �������� ��� ��...
// �ߺ����� �������� ���� �������� ���� ����...
void AZombieBaseCharacter::Attack()
{
	if (IsOverlap)
	{
		IsAttacking = true;
		FTimerHandle WaitHandle;
		float WaitTime = 1.5f;	// �ִϸ��̼� ����ð�
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
			{
				OnHit();
				OnAttackEnded();
			}), WaitTime, false);
	}
}

void AZombieBaseCharacter::OnAttackEnded()
{
	IsAttacking = false;

	OnAttackEnd.Broadcast();
}

void AZombieBaseCharacter::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	player = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (OtherActor == player)
	{
		IsOverlap = true;
	}
}

void AZombieBaseCharacter::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor == player)
	{
		IsOverlap = false;
	}
}


void AZombieBaseCharacter::OnHit()
{
	if (IsAttacking && IsOverlap)
	{
		FDamageEvent DamageEvent;
		UGameplayStatics::ApplyDamage(player, zombieDamage, GetController(), this, nullptr);
		//player->TakeDamage(zombieDamage, DamageEvent, GetController(), this);
	}
}

void AZombieBaseCharacter::Detect_Implementation()
{
	// �ڽ�Ŭ�������� �̵��ӵ� ����
	GLog->Log("Detect_Implementation Base Class : Need to Implementation at Child class");
}

void AZombieBaseCharacter::DetectOff_Implementation()
{
	GLog->Log("DetectOff_Implementation Base Class : Need to Implementation at Child class");
}