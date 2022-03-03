#include "Interactable.h"

AInteractable::AInteractable()
{
	interactableHelpText = FString("Press E to interact with item");
}

void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractable::Interact_Implementation()
{
	GLog->Log("Interact Base class(Interactable.cpp) : Need to Implementation at Child class");
}

