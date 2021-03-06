#include "TestDamageActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

ATestDamageActor::ATestDamageActor()
{
	CHelpers::CreateComponent<UBoxComponent>(this, &BoxCollision, "BoxCollision", RootComponent);
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh", BoxCollision);

	Mesh->SetRelativeScale3D(FVector(0.3f));

	Damage = 15.0f;
}

void ATestDamageActor::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ATestDamageActor::ActorBeginOverlap);

}

void ATestDamageActor::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, this, nullptr);
}
