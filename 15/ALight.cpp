#include "ALight.h"

AALight::AALight()
{
	CHelpers::CreateComponent<USceneComponent>(this, &SceneComp, "Scene", RootComponent);
	CHelpers::CreateComponent<UPointLightComponent>(this, &Light, "Light", SceneComp);
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Lamp, "Lamp", SceneComp);

	Light->Intensity = 1e+4f;
	Light->AttenuationRadius = 200.0f;
	idx = 0;
}

void AALight::BeginPlay()
{
	Super::BeginPlay();
	
	Light->SetVisibility(false);

	TArray<AActor*> Btns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInteractButton::StaticClass(), Btns);
	if (Btns.Num() > 0)
	{
		AInteractButton* interactBtn = Cast<AInteractButton>(Btns[idx]);
		interactBtn->LightOn.BindUFunction(this, "TurnOn");
		interactBtn->LightOff.BindUFunction(this, "TurnOff");
	}
}

void AALight::TurnOn()
{
	Light->SetVisibility(true);
}

void AALight::TurnOff()
{
	Light->SetVisibility(false);
}