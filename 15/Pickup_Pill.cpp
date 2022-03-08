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

	float remainHP = character->GetPlayerHP();
	if (remainHP > 80 && remainHP <= 100.0f)
	{
		character->SetPlayerHP(100.0f);
	}
	else if (remainHP <= 80.0f)
	{
		character->UpdatePlayerHP(healing);
	}
}