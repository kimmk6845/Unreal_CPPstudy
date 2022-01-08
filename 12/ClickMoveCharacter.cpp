// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickMoveCharacter.h"
#include <Engine/Classes/Components/CapsuleComponent.h>
#include <Engine/Classes/Camera/CameraComponent.h>
#include <Engine/Classes/GameFramework/CharacterMovementComponent.h>
#include <Engine/Classes/GameFramework/SpringArmComponent.h>

// Sets default values
AClickMoveCharacter::AClickMoveCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true; // BeginPlay가 동작한 직후 Tick 함수 동작

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// 카메라 회전에 따라 움직이지 않도록 함
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);	// 케릭터가 이동시키기 바로 직전에 이동방향과 현재 케릭터가 바라보는 방향이 다르면 초당 640도의 속도로 회전시킴
	GetCharacterMovement()->bConstrainToPlane = true;	// 케릭터 이동을 평면으로 제한
	GetCharacterMovement()->bSnapToPlaneAtStart = true; // 시작할 때 케릭터가 평면을 벗어난 상태면 가까운 평면으로 붙여서 시작


	// 스프링암
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetUsingAbsoluteRotation(true);		// 회전이 상위 컴포넌트를 따르지 않고 월드 좌표계를 따름
	SpringArmComponent->TargetArmLength = 800.0f;
	SpringArmComponent->SetRelativeRotation(FRotator(-60.0f, 45.0f, 0.0f));
	SpringArmComponent->bDoCollisionTest = false;

	// 카메라
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; // 카메라의 회전이 폰에 영향을 주지 않음
}

// Called when the game starts or when spawned
void AClickMoveCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClickMoveCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AClickMoveCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

