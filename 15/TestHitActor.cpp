#include "TestHitActor.h"
#include "Components/StaticMeshComponent.h"
#include "Global.h"

ATestHitActor::ATestHitActor()
{
	hp = 100.0f;

	CHelpers::CreateComponent<UStaticMeshComponent>(this, &mesh, "mesh");

}

void ATestHitActor::BeginPlay()
{
	Super::BeginPlay();
	
}

float ATestHitActor::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float GetDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	hp -= GetDamage;
	UE_LOG(LogTemp, Log, TEXT("Actor hp : %f"), hp);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Damage : %f"), GetDamage));

	if (hp <= 0.0f)
	{
		mesh->SetCollisionProfileName("NoCollision");

		Die();
	}

	return 0.0f;
}

void ATestHitActor::Die()
{
	this->Destroy();
}