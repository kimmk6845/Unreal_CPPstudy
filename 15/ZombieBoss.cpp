#include "ZombieBoss.h"
#include "GameFramework/CharacterMovementComponent.h"

AZombieBoss::AZombieBoss()
{
	zombieType = "Boss";
	baseHp = 3000.0f;
	zombieDamage = 40.0f;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;	// �ȱ� �̵��ӵ� (�߰� 500)

}

void AZombieBoss::Detect_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
}

void AZombieBoss::DetectOff_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
}