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
		// 게임 승리
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("YOU WIN."));
	}
	else
	{
		// 점령되지 않은 터렛이 있다는 출력문
		GLog->Log("Not enough condition");
	}
}
