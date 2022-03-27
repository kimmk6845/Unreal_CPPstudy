#include "InteractEscape.h"

AInteractEscape::AInteractEscape()
{
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &interactableMesh, "interactableMesh", RootComponent);
	interactableHelpText = FString("Press E to Escape the camp");
}

void AInteractEscape::Interact_Implementation()
{
	AFPSCharacter* character = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (character->GetOccupiedTurret() == 5)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("YOU WIN."));
		character->Win();
	}
	else
	{
		GLog->Log("Not enough condition");
	}
}
