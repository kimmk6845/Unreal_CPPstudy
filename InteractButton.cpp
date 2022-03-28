#include "InteractButton.h"

AInteractButton::AInteractButton()
{
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &interactableMesh, "interactMesh");
	interactableHelpText = FString("Press E to Turn on the light");
	bToggle = true;
}

void AInteractButton::Interact_Implementation()
{
	if (bToggle)
	{
		if (LightOn.IsBound())
			LightOn.Execute();
		interactableHelpText = FString("Press E to Turn off the light");
	}
	else
	{
		if (LightOff.IsBound())
			LightOff.Execute();
		interactableHelpText = FString("Press E to Turn on the light");
	}

	bToggle = !bToggle;
}