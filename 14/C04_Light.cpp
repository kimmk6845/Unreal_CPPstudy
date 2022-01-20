#include "C04_Light.h"
#include "Global.h"
#include "C03_Trigger.h"
#include "Components/TextRenderComponent.h"
#include "Components/PointLightComponent.h"

AC04_Light::AC04_Light()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);
	CHelpers::CreateComponent<UPointLightComponent>(this, &Light, "Light", Scene);

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());

	Light->Intensity = 1e+4f;	// 10^4 = 10000
	Light->AttenuationRadius = 200.0f;
	Light->LightColor = FColor(255, 128, 50);
}

void AC04_Light::BeginPlay()
{
	Super::BeginPlay();

	Light->SetVisibility(false);

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC03_Trigger::StaticClass(), actors);
	CheckFalse(actors.Num() > 0);

	AC03_Trigger* trigger = Cast<AC03_Trigger>(actors[0]);
	trigger->OnBoxLightBeginOverlap.BindUFunction(this, "OnLight");
	trigger->OnBoxLightEndOverlap.BindUFunction(this, "OffLight");
}

void AC04_Light::OnLight()
{
	Light->SetVisibility(true);
}

void AC04_Light::OffLight()
{
	Light->SetVisibility(false);
}
