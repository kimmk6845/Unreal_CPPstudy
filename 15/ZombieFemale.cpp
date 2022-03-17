#include "ZombieFemale.h"
#include "GameFramework/CharacterMovementComponent.h"

AZombieFemale::AZombieFemale()
{
	zombieType = "Female";
	baseHp = 800.0f;
	zombieDamage = 20.0f;
	GetCharacterMovement()->MaxWalkSpeed = 100.0f;	// 걷기 이동속도 (추격 400)
	GetMesh()->SetCollisionProfileName("FemaleZombie");

}

void AZombieFemale::Detect_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
}

void AZombieFemale::DetectOff_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = 100.0f;
}