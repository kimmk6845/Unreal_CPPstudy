#include "ZombieMale1.h"
#include "GameFramework/CharacterMovementComponent.h"

AZombieMale1::AZombieMale1()
{
	zombieType = "Male1";
	baseHp = 600.0f;
	zombieDamage = 30.0f;
	GetCharacterMovement()->MaxWalkSpeed = 100.0f;	// �ȱ� �̵��ӵ� (�߰� 400)

}

void AZombieMale1::Detect_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
}

void AZombieMale1::DetectOff_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = 100.0f;
}