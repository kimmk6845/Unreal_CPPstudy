#include "ASensorLight.h"

AASensorLight::AASensorLight()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene", RootComponent);
	CHelpers::CreateComponent<UBoxComponent>(this, &BoxCollision, "BoxCollision", Scene);
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &SensorLamp, "SensorLamp", Scene);
	CHelpers::CreateComponent<UPointLightComponent>(this, &PointLight, "PointLight", SensorLamp);

	SensorLamp->SetRelativeLocation(FVector(0.0f, 0.0f, 300.0f));
	PointLight->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
	BoxCollision->SetRelativeScale3D(FVector(3.0f));
	PointLight->SetVisibility(true);

	bDelayToggle = false;
	WaitTime = 5.0f;
}

void AASensorLight::BeginPlay()
{
	Super::BeginPlay();
	
	PointLight->SetVisibility(false);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AASensorLight::ComponentBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AASensorLight::ComponentEndOverlap);
}

void AASensorLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bDelayToggle)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, FString::Printf(TEXT("%f"), WaitTime));
		WaitTime -= DeltaTime * 1.0f;

		if (WaitTime < 0.0f)
		{
			PointLight->SetVisibility(false);
			WaitTime = 5.0f;
			bDelayToggle = false;
		}
	}
}

void AASensorLight::ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Log, TEXT("Begin Overlap"));
	PointLight->SetVisibility(true);
}

void AASensorLight::ComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Log, TEXT("End Overlap"));

	// 5초 후 꺼지도록
	if (WaitTime == 5.0f)
	{
		bDelayToggle = true;
	}
}
