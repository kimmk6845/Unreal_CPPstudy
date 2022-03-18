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
		// ���� �¸�
	}
	else
	{
		// ���ɵ��� ���� �ͷ��� �ִٴ� ��¹�
	}
}
