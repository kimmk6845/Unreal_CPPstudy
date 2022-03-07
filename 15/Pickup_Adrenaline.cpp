#include "Pickup_Adrenaline.h"

APickup_Adrenaline::APickup_Adrenaline()
{
	itemName = FString("Adrenaline");
	advanceDamage = 10.0f;

	interactableMesh->SetRelativeScale3D(FVector(0.1f));
}

void APickup_Adrenaline::Use_Implementation()
{
	GLog->Log(TEXT("Use Adrenaline"));
	AFPSCharacter* character = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	character->UpdateAdvanceDamage(advanceDamage);
	character->UseAdrenaline();
	character->AdrenalineBuffOn();
}

