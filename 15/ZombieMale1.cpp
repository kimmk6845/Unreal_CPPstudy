#include "ZombieMale1.h"
#include "GameFramework/CharacterMovementComponent.h"

AZombieMale1::AZombieMale1()
{
	zombieType = "Male1";
	baseHp = 600.0f;
	zombieDamage = 30.0f;
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;	// �߰ݽ� �̵��ӵ� (�ȱ� 100)

}