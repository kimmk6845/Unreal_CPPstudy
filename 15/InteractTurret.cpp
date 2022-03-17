#include "InteractTurret.h"

AInteractTurret::AInteractTurret()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<UStaticMeshComponent>(this, &TurretBottomMesh, "TurretBottomMesh", RootComponent);
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &interactableMesh, "interactableMesh", TurretBottomMesh);
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &TurretTopMesh, "TurretMesh", TurretBottomMesh);
	CHelpers::CreateComponent<UPointLightComponent>(this, &Light, "Light", TurretTopMesh);
	CHelpers::CreateComponent<UWidgetComponent>(this, &widget, "widget", TurretTopMesh);
	interactableHelpText = FString("Press E to occupy the turret");
	occupyPercent = 0.0f;
	cnt = 0;
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
		if (occupyPercent < 100.0f)
		{
			occupyPercent += DeltaTime * 30.0f;		// 점령까지 약 33초 소요	(30은 임시 --> 3.0f로 변경....)
			TurretWidget->SetOccupyBar(occupyPercent);
		}
	}

	if (player->currentInteractable == nullptr)		// e를 누른채 멀리 떨어지면 점령이 끊어짐
	{
		IsOccupying = false;
		widget->SetVisibility(false);
		interactableHelpText = FString("Press E to occupy the turret");
	}

	if (occupyPercent >= 100.0f)
	{
		interactableHelpText = FString("");
		Light->SetVisibility(true);
		widget->SetVisibility(false);

		float roll = TurretTopMesh->GetComponentRotation().Roll;
		float pitch = TurretTopMesh->GetComponentRotation().Pitch;
		float Yaw = TurretTopMesh->GetComponentRotation().Yaw + DeltaTime * 30.0f;

		TurretTopMesh->SetRelativeRotation(FRotator(pitch, Yaw, roll));

		if (cnt == 0)
		{
			cnt++;
			Succeed();
		}
	}
}

void AInteractTurret::Interact_Implementation()
{
	IsOccupying = true;
	widget->SetVisibility(true);
	interactableHelpText = FString("Wait...");
}

void AInteractTurret::InteractOff_Implementation()
{
	IsOccupying = false;
	widget->SetVisibility(false);
	interactableHelpText = FString("Press E to occupy the turret");
}

void AInteractTurret::Succeed()
{
	player->AddOccupiedTerritory();
}