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

	const float TimeBetweenCameraChanges = 2.0f;	// 다음 카메라로 전환하는데 시간
	const float SmoothBlendTime = 0.75f;	// 부드럽게 전환될 시간
	
	TimeToNextCameraChange -= DeltaTime;
	if (TimeToNextCameraChange <= 0)
	{
		TimeToNextCameraChange += TimeBetweenCameraChanges;

		// 카메라 전환
		APlayerController* controller = UGameplayStatics::GetPlayerController(this, 0);
		if (controller)
		{
			if ((controller->GetViewTarget() != CameraOne) && (CameraOne != nullptr))	// 바라보는 타겟이 카메라1이 아니면
				controller->SetViewTarget(CameraOne);	// 카메라 전환때 바로 컷해서 들어감
			else if((controller->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr))
				controller->SetViewTargetWithBlend(CameraTwo,SmoothBlendTime);	// 카메라 전환때 부드럽게 전환
		}
	}

}

