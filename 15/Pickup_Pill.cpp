#include "Pickup_Pill.h"

APickup_Pill::APickup_Pill()
{
	itemName = FString("Pill");
	healing = 20.0f;
}

void APickup_Pill::Use_Implementation()
{
	GLog->Log(TEXT("Use Pill"));
	AFPSCharacter* character = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	character->SetPlayerHP(healing);
}