// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float TimeBetweenCameraChanges = 2.0f;	// ���� ī�޶�� ��ȯ�ϴµ� �ð�
	const float SmoothBlendTime = 0.75f;	// �ε巴�� ��ȯ�� �ð�
	
	TimeToNextCameraChange -= DeltaTime;
	if (TimeToNextCameraChange <= 0)
	{
		TimeToNextCameraChange += TimeBetweenCameraChanges;

		// ī�޶� ��ȯ
		APlayerController* controller = UGameplayStatics::GetPlayerController(this, 0);
		if (controller)
		{
			if ((controller->GetViewTarget() != CameraOne) && (CameraOne != nullptr))	// �ٶ󺸴� Ÿ���� ī�޶�1�� �ƴϸ�
				controller->SetViewTarget(CameraOne);	// ī�޶� ��ȯ�� �ٷ� ���ؼ� ��
			else if((controller->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr))
				controller->SetViewTargetWithBlend(CameraTwo,SmoothBlendTime);	// ī�޶� ��ȯ�� �ε巴�� ��ȯ
		}
	}

}

