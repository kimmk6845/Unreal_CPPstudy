#include "Pickup_PainKiller.h"

// 스테미너 100% 회복
APickup_PainKiller::APickup_PainKiller()
{
	itemName = FString("PainKiller");
	Stamina = 100.0f;
}

void APickup_PainKiller::Use_Implementation()
{
	GLog->Log(TEXT("Use PainKiller"));
	AFPSCharacter* character = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	character->SetPlayerStamina(Stamina);
}