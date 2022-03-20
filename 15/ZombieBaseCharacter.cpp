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

	// AI컨트롤 클래스 부여
	CHelpers::GetClass<AController>(&AIControllerClass, "Blueprint'/Game/_My/Blueprints/Zombie/BP_ZombieAIController'");
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	// AIControllerClass = AZombieAIController::StaticClass();	// C 클래스
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

// 공격애니메이션에 맞춰서 데미지를 줘야 함... &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// 중복으로 여러번에 거쳐 데미지가 들어가고 있음... &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void AZombieBaseCharacter::Attack()
{
	if (IsOverlap)
	{
		IsAttacking = true;
		FTimerHandle WaitHandle;
		float WaitTime = 1.5f;	// 애니메이션 실행시간
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
			{
				OnHit();
				OnAttackEnded();
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, TEXT("attack"));
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
	overlapActor = OtherActor;
	if (overlapActor->ActorHasTag("Player"))
	{
		IsOverlap = true;
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Overlap"));
	}
}

void AZombieBaseCharacter::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (overlapActor->ActorHasTag("Player"))
	{
		IsOverlap = false;
	}
}


void AZombieBaseCharacter::OnHit()
{
	if (IsAttacking && IsOverlap && overlapActor->ActorHasTag("Player"))
	{
		FDamageEvent DamageEvent;
		overlapActor->TakeDamage(zombieDamage, DamageEvent, GetController(), this);
	}
}

void AZombieBaseCharacter::Detect_Implementation()
{
	// 자식클래스에서 이동속도 조절
	GLog->Log("Detect_Implementation Base Class : Need to Implementation at Child class");
}

void AZombieBaseCharacter::DetectOff_Implementation()
{
	GLog->Log("DetectOff_Implementation Base Class : Need to Implementation at Child class");
}