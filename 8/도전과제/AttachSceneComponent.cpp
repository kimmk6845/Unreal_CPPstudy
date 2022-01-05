// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachSceneComponent.h"

// Sets default values for this component's properties
UAttachSceneComponent::UAttachSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttachSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	// 컴포넌트를 붙일 때는 SetupAttachment 함수를 사용했는데 액터를 붙일 때는 AttachToActor 함수 사용
	TargetActor->AttachToActor(ParentActor, FAttachmentTransformRules::KeepRelativeTransform);
	
}


// Called every frame
void UAttachSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

