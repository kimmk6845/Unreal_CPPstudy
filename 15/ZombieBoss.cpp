#include "ZombieBoss.h"
#include "GameFramework/CharacterMovementComponent.h"

AZombieBoss::AZombieBoss()
{
	zombieType = "Boss";
	baseHp = 3000.0f;
	zombieDamage = 40.0f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;	// �߰ݽ� �̵��ӵ� (�ȱ� 200)

}