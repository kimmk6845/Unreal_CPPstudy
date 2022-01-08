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
	PrimaryActorTick.bStartWithTickEnabled = true; // BeginPlay�� ������ ���� Tick �Լ� ����

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// ī�޶� ȸ���� ���� �������� �ʵ��� ��
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);	// �ɸ��Ͱ� �̵���Ű�� �ٷ� ������ �̵������ ���� �ɸ��Ͱ� �ٶ󺸴� ������ �ٸ��� �ʴ� 640���� �ӵ��� ȸ����Ŵ
	GetCharacterMovement()->bConstrainToPlane = true;	// �ɸ��� �̵��� ������� ����
	GetCharacterMovement()->bSnapToPlaneAtStart = true; // ������ �� �ɸ��Ͱ� ����� ��� ���¸� ����� ������� �ٿ��� ����


	// ��������
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetUsingAbsoluteRotation(true);		// ȸ���� ���� ������Ʈ�� ������ �ʰ� ���� ��ǥ�踦 ����
	SpringArmComponent->TargetArmLength = 800.0f;
	SpringArmComponent->SetRelativeRotation(FRotator(-60.0f, 45.0f, 0.0f));
	SpringArmComponent->bDoCollisionTest = false;

	// ī�޶�
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; // ī�޶��� ȸ���� ���� ������ ���� ����
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

