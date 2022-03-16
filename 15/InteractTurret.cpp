#include "InteractTurret.h"

AInteractTurret::AInteractTurret()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<UStaticMeshComponent>(this, &interactableMesh, "interactableMesh", RootComponent);
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &TurretMesh, "TurretMesh", interactableMesh);
	CHelpers::CreateComponent<UPointLightComponent>(this, &Light, "Light", interactableMesh);
	CHelpers::CreateComponent<UWidgetComponent>(this, &widget, "widget", interactableMesh);
	interactableHelpText = FString("Press E to occupy the turret");
	occupyPercent = 0.0f;
}

void AInteractTurret::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(this,0));
	TurretWidget = Cast<UTurretWidget>(widget->GetUserWidgetObject());
	Light->SetVisibility(false);
	widget->SetVisibility(false);
}

void AInteractTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsOccupying)
	{
		GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::White, FString::Printf(TEXT("Percent : %f"), occupyPercent));
		if (occupyPercent >= 100.0f)
		{
			interactableHelpText = FString("");
			Light->SetVisibility(true);
			widget->SetVisibility(false);
		}
		else
		{
			occupyPercent += DeltaTime * 3.0f;		// 점령까지 약 33초 소요		
			TurretWidget->SetOccupyBar(occupyPercent);
		}
	}

	if (player->currentInteractable == nullptr)		// e를 누른채 멀리 떨어지면 점령이 끊어짐
	{
		IsOccupying = false;
	}
}

void AInteractTurret::Interact_Implementation()
{
	IsOccupying = true;
	widget->SetVisibility(true);
}

void AInteractTurret::InteractOff_Implementation()
{
	IsOccupying = false;
	widget->SetVisibility(false);
}
