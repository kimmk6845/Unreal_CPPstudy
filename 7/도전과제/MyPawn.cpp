// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include <Engine/Classes/Camera/CameraComponent.h>

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ������ ���۵Ǹ� �ڵ����� �÷��̾��� �Է��� ����
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurCamera->SetupAttachment(RootComponent);	// ī�޶� ��Ʈ�� ���̰�
	OurCamera->SetRelativeLocation(FVector(-250.f, 0.0f, 250.0f));		// ��ġ�� ȸ���� ������
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

	// ���̰� �� ��ü
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


	// Grow Ű�� ���� ������ ó��
	{
		float CurrentScale = OurVisibleComponent->GetComponentScale().X;
		if (bGrowing)
		{
			// �������� (2)
			if (InputTime > 0.0f && InputTime <= 0.5f)
			{
				// �̵�Ű�� �Է��� ���ķ� �Ǵ�
				CurrentScale = 2.0f;
			}
			else	// �Է��� ���İ� �ƴϸ� õõ�� Ŀ��
				CurrentScale += DeltaTime;
		}
		else
		{
			CurrentScale -= DeltaTime * 0.5f;
		}

		CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);	// ũ�Ⱑ �ʹ� Ŀ���ų� �۾����� �� ����
		OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale)); // ������ ����
	}

	// �̵� ó��
	{
		if (!CurrentVelocity.IsZero())
		{
			InputTime += DeltaTime;	
			float Speed = InputTime * 0.2f;					// �ӷ� ���
			Speed = FMath::Clamp(InputTime, 1.0f, 5.0f);	// �ӵ� ����
			FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime * Speed);
			SetActorLocation(NewLocation);
		}
		else
			InputTime = 0.0f;	// �Է��� ������ �ʴ� ���� 0
	}
	
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// �׼� ����
	PlayerInputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	PlayerInputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	// �� ����
	PlayerInputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);

}


// �÷��̾� �Է� ó�� �Լ� (1�ܰ�, ���ε�������� ��)
void AMyPawn::Move_XAxis(float AxisValue)
{
	// AxisValue�� �����ϴ� ������ �� �������� WŰ�� ���� ����Ű�� ��ϵǾ� ���� �� �̵��ӵ��� 2�谡 �Ǵ� ���� ���� 
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