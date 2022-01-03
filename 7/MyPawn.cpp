// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include <Engine/Classes/Camera/CameraComponent.h>

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 게임이 시작되면 자동으로 플레이어의 입력이 연결
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurCamera->SetupAttachment(RootComponent);	// 카메라를 루트에 붙이고
	OurCamera->SetRelativeLocation(FVector(-250.f, 0.0f, 250.0f));		// 위치와 회전을 정해줌
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

	// 보이게 될 몸체
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// Grow 키에 대한 반응을 처리
	{
		float CurrentScale = OurVisibleComponent->GetComponentScale().X;
		if (bGrowing)
			CurrentScale += DeltaTime;
		else
			CurrentScale -= DeltaTime * 0.5f;

		CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);	// 크기가 너무 커지거나 작아지는 것 방지
		OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale)); // 스케일 적용
	}

	// 이동 처리
	{
		if (!CurrentVelocity.IsZero())
		{
			FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
			SetActorLocation(NewLocation);
		}
	}
	
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 액션 매핑
	PlayerInputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	PlayerInputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	// 축 매핑
	PlayerInputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);

}


// 플레이어 입력 처리 함수 (1단계, 바인딩시켜줘야 함)
void AMyPawn::Move_XAxis(float AxisValue)
{
	// AxisValue를 제한하는 이유는 축 매핑으로 W키와 위쪽 방향키가 등록되어 있을 때 이동속도가 2배가 되는 것을 막음 
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.f;
}

void AMyPawn::Move_YAxis(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.f;
}

void AMyPawn::StartGrowing()
{
	bGrowing = true;
}

void AMyPawn::StopGrowing()
{
	bGrowing = false;
}