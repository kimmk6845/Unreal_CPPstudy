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

	float remainHP = character->GetPlayerHP();
	if (remainHP > 40 && remainHP <= 100.0f)
	{
		character->SetPlayerHP(100.0f);
	}
	else if (remainHP <= 40.0f)
	{
		character->UpdatePlayerHP(healing);
	}

}