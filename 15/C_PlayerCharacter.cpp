#include "C_PlayerCharacter.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

AC_PlayerCharacter::AC_PlayerCharacter()
{
	//PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<UCameraComponent>(this, &camera, "camera", GetCapsuleComponent());
	camera->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0 + BaseEyeHeight));	// 케릭터 눈 위치보다 살짝 높게
	camera->bUsePawnControlRotation = true;		// 폰이 카메라 로테이션 제어

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	// 1인칭 스켈레탈 메시 컴포넌트 생성
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &FPSMesh, "FPSMesh", camera);
	FPSMesh->SetRelativeLocation(FVector(50.0f, -5.0f, -150.0f));
	FPSMesh->SetRelativeRotation(FRotator(25.0f, 350.0f, 0.0f));
	FPSMesh->SetOnlyOwnerSee(true);			// 소유자만 메시를 볼 수 있도록 설정
	FPSMesh->bCastDynamicShadow = false;	// 그림자 제거
	FPSMesh->CastShadow = false;

	GetMesh()->SetOwnerNoSee(true);			// 소유자는 3인칭 메시를 볼 수 없도록 설정

	CHelpers::CreateComponent<UStaticMeshComponent>(this, &FPSGun, "FPSGun", FPSMesh);
	FPSGun->SetRelativeLocation(FVector(56.4f, 16.0f, 121.0f));
	FPSGun->SetRelativeRotation(FRotator(2.45f, -88.0f, 16.9f));
	FPSGun->SetRelativeScale3D(FVector(0.3f));
	FPSGun->bCastDynamicShadow = false;
	FPSGun->CastShadow = false;

	Tags.Add("User");
}

//void AC_PlayerCharacter::BeginPlay()
//{
//	Super::BeginPlay();
//
//	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Setting Character!"));
//}
//
//void AC_PlayerCharacter::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void AC_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &AC_PlayerCharacter::OnMoveForward);
	InputComponent->BindAxis("MoveRight", this, &AC_PlayerCharacter::OnMoveRight);
	InputComponent->BindAxis("HorizontalLook", this, &AC_PlayerCharacter::OnHorizontalLook);
	InputComponent->BindAxis("VerticalLook", this, &AC_PlayerCharacter::OnVerticalLook);

	InputComponent->BindAction("Running", IE_Pressed, this, &AC_PlayerCharacter::OnRunning);
	InputComponent->BindAction("Running", IE_Released, this, &AC_PlayerCharacter::OffRunning);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AC_PlayerCharacter::StartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AC_PlayerCharacter::StopJump);
	InputComponent->BindAction("Fire", IE_Pressed, this, &AC_PlayerCharacter::OnFire);
	InputComponent->BindAction("Fire", IE_Released, this, &AC_PlayerCharacter::OffFire);
}


/////////////
// 축 매핑
void AC_PlayerCharacter::OnMoveForward(float Axis)
{
	//FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	//AddMovementInput(Direction, Axis);

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);

}

void AC_PlayerCharacter::OnMoveRight(float Axis)
{
	//FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	//AddMovementInput(Direction, Axis);

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void AC_PlayerCharacter::OnHorizontalLook(float Axis)
{
	AddControllerYawInput(Axis);
}

void AC_PlayerCharacter::OnVerticalLook(float Axis)
{
	AddControllerPitchInput(Axis);
}

/////////////



/////////////
// 액션 매핑
void AC_PlayerCharacter::OnRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void AC_PlayerCharacter::OffRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
}

void AC_PlayerCharacter::StartJump()
{
	bPressedJump = true;
}

void AC_PlayerCharacter::StopJump()
{
	bPressedJump = false;
}

void AC_PlayerCharacter::Fire()
{

	FVector CameraLocaton;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocaton, CameraRotation);

	FVector MuzzleLocation = CameraLocaton + FTransform(CameraRotation).TransformVector(MuzzleOffset + FVector(10, 30, 15));
	FRotator MuzzleRotation = CameraRotation + FRotator(1.0f, -0.4f, 0.0f);

	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		if (IsFiring)
		{
			AC_FPSProjectile* Projectile = World->SpawnActor<AC_FPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		
			// 자동연사
			GetWorld()->GetTimerManager().SetTimer(timer, this, &AC_PlayerCharacter::Fire, 0.09f, false);
		}

	}
}

void AC_PlayerCharacter::OnFire()
{
	IsFiring = true;
	Fire();
}

void AC_PlayerCharacter::OffFire()
{
	IsFiring = false;
}

// AI 시각 자극
void AC_PlayerCharacter::setup_stimulus()
{
	stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("stimulus"));
	stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	stimulus->RegisterWithPerceptionSystem();
}
