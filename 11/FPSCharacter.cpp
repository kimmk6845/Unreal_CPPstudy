// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include <Engine/Classes/Components/CapsuleComponent.h>

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// 카메라 생성 및 위치 조정
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPSCameraComponent->SetupAttachment(GetCapsuleComponent());
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0 + BaseEyeHeight));	// 케릭터 눈 위치보다 살짝 높게
	FPSCameraComponent->bUsePawnControlRotation = true;		// 폰이 카메라 로테이션 제어

	// 1인칭 스켈레탈 메시 컴포넌트 생성
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	FPSMesh->SetOnlyOwnerSee(true);			// 소유자만 메시를 볼 수 있도록 설정
	FPSMesh->SetupAttachment(FPSCameraComponent);
	FPSMesh->bCastDynamicShadow = false;	// 그림자 제거
	FPSMesh->CastShadow = false;

	GetMesh()->SetOwnerNoSee(true);			// 소유자는 3인칭 메시를 볼 수 없도록 설정
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 현재 케릭터가 사용되는지 TEST
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

	// 이동함수 바인딩
	InputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	// 마우스 회전 바인딩 (함수 내장되어있음)
	InputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);


	// 점프 매핑 (변수 내장되어있음)
	InputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);

	// 발사 함수 매핑
	InputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);

}


// 이동함수 구현
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
	// 내장 변수만 조작
	bPressedJump = true;
}

void AFPSCharacter::StopJump()
{
	bPressedJump = false;
}


// 발사 함수 구현
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