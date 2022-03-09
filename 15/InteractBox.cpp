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

	if (BoxHP > 0)	// �������� ������ ���ڰ� �μ����Ƿ� ��ȣ�ۿ� �ؽ�Ʈ�� ������
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
