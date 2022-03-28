#include "ZombieMale2.h"
#include "GameFramework/CharacterMovementComponent.h"

AZombieMale2::AZombieMale2()
{
	zombieType = "Male2";
	baseHp = 600.0f;
	zombieDamage = 20.0f;
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;	// 걷기 이동속도 (추격 300)

}

void AZombieMale2::Detect_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void AZombieMale2::DetectOff_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
}