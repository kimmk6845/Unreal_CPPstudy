#include "InteractBox.h"

AInteractBox::AInteractBox()
{
	BoxHP = 50.0f;
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &BoxBody, "BoxBody", RootComponent);
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &interactableMesh, "interactBox", BoxBody);
	CHelpers::CreateComponent<UDestructibleComponent>(this, &Boxdebris, "Boxdebris", BoxBody);

	BoxBody->SetCollisionProfileName("InvisibleWall");
	interactableHelpText = FString("Press E to Open the box");
	interactableMesh->SetSimulatePhysics(true);
}

float AInteractBox::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float GetDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (BoxHP > 0)	// 데미지를 받으면 상자가 부서지므로 상호작용 텍스트를 제거함
	{
		interactableHelpText = FString("");
		BoxHP -= GetDamage;
	}
	else
		this->Destroy();

	return 0.0f;
}

void AInteractBox::Interact_Implementation()
{
	Boxdebris->SetCollisionProfileName("DestructibleOpenBox");
	interactableMesh->DestroyComponent();
}
