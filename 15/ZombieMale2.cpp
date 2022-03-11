#include "ZombieMale2.h"
#include "GameFramework/CharacterMovementComponent.h"

AZombieMale2::AZombieMale2()
{
	zombieType = "Male2";
	baseHp = 600.0f;
	zombieDamage = 20.0f;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;	// 추격시 이동속도 (걷기 150)

}