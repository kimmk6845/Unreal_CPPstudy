#include "RotatingMovementActor.h"

ARotatingMovementActor::ARotatingMovementActor()
{

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;

	RotateSpeed = 100.0f;
	Movement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("MOVEMENT"));
	Movement->RotationRate = FRotator(0.0f, RotateSpeed, 0.0f);
}

void ARotatingMovementActor::BeginPlay()
{
	Super::BeginPlay();
	
}