#include "ZombieFemale.h"
#include "GameFramework/CharacterMovementComponent.h"

AZombieFemale::AZombieFemale()
{
	zombieType = "Female";
	baseHp = 800.0f;
	zombieDamage = 20.0f;
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;	// �߰ݽ� �̵��ӵ� (�ȱ� 100)
	GetMesh()->SetCollisionProfileName("FemaleZombie");

}