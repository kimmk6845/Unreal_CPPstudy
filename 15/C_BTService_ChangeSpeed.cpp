#include "C_BTService_ChangeSpeed.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "C_AIController.h"
#include "C_ZombieCharacter.h"

UC_BTService_ChangeSpeed::UC_BTService_ChangeSpeed()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Change Speed");
}

void UC_BTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::OnBecomeRelevant(owner_comp, node_memory);
	auto const cont = owner_comp.GetAIOwner();
	AC_ZombieCharacter* const Bot = Cast<AC_ZombieCharacter>(cont->GetPawn());
	Bot->GetCharacterMovement()->MaxWalkSpeed = speed;
}

FString UC_BTService_ChangeSpeed::GetStaticServiceDescription() const
{
	return FString("Change the Bot speed");
}
