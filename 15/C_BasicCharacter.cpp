#include "C_BasicCharacter.h"

AC_BasicCharacter::AC_BasicCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AC_BasicCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_BasicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_BasicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

