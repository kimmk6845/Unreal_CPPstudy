#include "FPSOnHitActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Global.h"

AFPSOnHitActor::AFPSOnHitActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	Box->SetSimulatePhysics(true);
	Box->SetLinearDamping(3.0f);
	Box->SetAngularDamping(1.0f);

	RootComponent = Box;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);


	MaxHealth = 100.0f;
	Health = MaxHealth;

	Tags.Add("Enemy");	// Actor Has Tags
}

void AFPSOnHitActor::BeginPlay()
{
	Super::BeginPlay();

}

void AFPSOnHitActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSOnHitActor::OnHit(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{

}

float AFPSOnHitActor::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float GetDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	Health -= GetDamage;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("HP : %f"), Health));

	if (Health <= 0.0f)
	{
		this->Destroy();
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Destroy!!"));
	}

	return 0.0f;
}