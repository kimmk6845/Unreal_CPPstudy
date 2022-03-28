#include "PickupItemBase.h"

APickupItemBase::APickupItemBase()
{
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &interactableMesh, "PickUpMesh");
	interactableMesh->SetSimulatePhysics(false);

	itemName = FString(" ");
	interactableHelpText = FString("Press E to pick up");
}

void APickupItemBase::BeginPlay()
{
	interactableHelpText = FString::Printf(TEXT("%s : Press E to pick up"), *itemName);
}

void APickupItemBase::Interact_Implementation()
{
	AFPSCharacter* character = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (character->AddItemToInventory(this))
	{
		OnPickUp();
	}
}

void APickupItemBase::Use_Implementation()
{
	GLog->Log("Use Base class(PickupItemBase.cpp) : Need to Implementation at Child class");
}

void APickupItemBase::OnPickUp()
{
	interactableMesh->SetVisibility(false);
	interactableMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
