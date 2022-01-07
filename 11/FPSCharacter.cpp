// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include <Engine/Classes/Components/CapsuleComponent.h>

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// ī�޶� ���� �� ��ġ ����
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPSCameraComponent->SetupAttachment(GetCapsuleComponent());
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0 + BaseEyeHeight));	// �ɸ��� �� ��ġ���� ��¦ ����
	FPSCameraComponent->bUsePawnControlRotation = true;		// ���� ī�޶� �����̼� ����

	// 1��Ī ���̷�Ż �޽� ������Ʈ ����
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	FPSMesh->SetOnlyOwnerSee(true);			// �����ڸ� �޽ø� �� �� �ֵ��� ����
	FPSMesh->SetupAttachment(FPSCameraComponent);
	FPSMesh->bCastDynamicShadow = false;	// �׸��� ����
	FPSMesh->CastShadow = false;

	GetMesh()->SetOwnerNoSee(true);			// �����ڴ� 3��Ī �޽ø� �� �� ������ ����
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// ���� �ɸ��Ͱ� ���Ǵ��� TEST
	if (GEngine)
	{	
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter"));
	}
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// �̵��Լ� ���ε�
	InputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	// ���콺 ȸ�� ���ε� (�Լ� ����Ǿ�����)
	InputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);


	// ���� ���� (���� ����Ǿ�����)
	InputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);

	// �߻� �Լ� ����
	InputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);

}


// �̵��Լ� ����
void AFPSCharacter::MoveForward(float AxisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, AxisValue);
}

void AFPSCharacter::MoveRight(float AxisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, AxisValue);
}

void AFPSCharacter::StartJump()
{
	// ���� ������ ����
	bPressedJump = true;
}

void AFPSCharacter::StopJump()
{
	bPressedJump = false;
}


// �߻� �Լ� ����
void AFPSCharacter::Fire()
{
	FVector CameraLocaton;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocaton, CameraRotation);

	FVector MuzzleLocation = CameraLocaton + FTransform(CameraRotation).TransformVector(MuzzleOffset);
	FRotator MuzzleRotation = CameraRotation;
	MuzzleRotation.Pitch += 10.0f;

	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
		if (Projectile)
		{
			FVector LaunchDirection = MuzzleRotation.Vector();
			Projectile->FireInDirection(LaunchDirection);
		}
	}
}