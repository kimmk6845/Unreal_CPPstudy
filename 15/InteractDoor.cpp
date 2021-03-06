#include "InteractDoor.h"

AInteractDoor::AInteractDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	bOpen = false;
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &DoorFrame, "DoorFrame", RootComponent);
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &interactableMesh, "interactDoor",DoorFrame);
	interactableHelpText = FString("Press E to Open the door");
	interactableMesh->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));	// ai 네비게이션을 위해 열어둠
}

void AInteractDoor::BeginPlay()
{
	Super::BeginPlay();

	interactableMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
}

void AInteractDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float RotationRoll = interactableMesh->GetRelativeRotation().Roll;
	float RotationPitch = interactableMesh->GetRelativeRotation().Pitch;
	float RotationYaw = interactableMesh->GetRelativeRotation().Yaw;

	if (bOpen)
	{
		// 열리는 동작
		if (RotationYaw <= 90.0f)
		{
			RotationYaw += DeltaTime * 200.0f;
			interactableMesh->SetRelativeRotation(FRotator(RotationPitch, RotationYaw, RotationRoll));
		}
	}
	else
	{
		// 닫히는 동작
		if (RotationYaw >= 0)
		{
			RotationYaw -= DeltaTime * 200.0f;
			interactableMesh->SetRelativeRotation(FRotator(RotationPitch, RotationYaw, RotationRoll));
		}

	}
}

void AInteractDoor::Interact_Implementation()
{
	bOpen = !bOpen;

	// tick에서 처리될 것. 동작 확인만 하기 위함
	if (bOpen)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Open Door"));
		interactableHelpText = FString("Press E to Close the door");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Close Door"));
		interactableHelpText = FString("Press E to Open the door");
	}

}