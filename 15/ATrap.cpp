#include "ATrap.h"

AATrap::AATrap()
{
	PrimaryActorTick.bCanEverTick = true;

	Damage = 60.0f;
	GetDamaged = false;

	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UBoxComponent>(this, &BoxCollision, "BoxCollision", Scene);
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &TrapMeshBody, "TrapMeshBody", Scene);
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &TrapMesh1, "TrapMesh1", TrapMeshBody);
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &TrapMesh2, "TrapMesh2", TrapMeshBody);

	TrapMeshBody->SetRelativeScale3D(FVector(0.2f));
	BoxCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));

}

void AATrap::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AATrap::ActorBeginOverlap);

	player = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
}

void AATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsOverlap)
	{
		float roll = TrapMesh1->GetRelativeRotation().Roll + (DeltaTime * 200.0f);
		if (roll <= 60.0f)
		{
			TrapMesh1->SetRelativeRotation(FRotator(0.0f, 0.0f, roll));
			TrapMesh2->SetRelativeRotation(FRotator(0.0f, 0.0f, -roll));
		}
	}
}

void AATrap::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor == player)
	{
		IsOverlap = true;

		if (GetDamaged == false)
		{
			UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, this, nullptr);
			GetDamaged = true;
		}
	}
}
