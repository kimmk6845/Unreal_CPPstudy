#include "Pickup_FirstAidKit.h"
#include "FPSCharacter.h"

APickup_FirstAidKit::APickup_FirstAidKit()
{
	itemName = FString("FIRST AID KIT");
	healing = 60.0f;
}

void APickup_FirstAidKit::Use_Implementation()
{
	GLog->Log(TEXT("Use First Aid Kit"));
	AFPSCharacter* character = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	character->SetPlayerHP(healing);
}