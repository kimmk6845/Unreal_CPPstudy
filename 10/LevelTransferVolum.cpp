// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTransferVolum.h"
#include "OpenLevelCharacter.h"
#include <Engine/Classes/Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>	// 레벨 이동
// Sets default values
ALevelTransferVolum::ALevelTransferVolum()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	TransferVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TransferVolume"));
	RootComponent = TransferVolume;
	TransferVolume->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));	// 폰만 감지하도록
}

// Called when the game starts or when spawned
void ALevelTransferVolum::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelTransferVolum::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ALevelTransferVolum::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AOpenLevelCharacter* Character = Cast<AOpenLevelCharacter>(OtherActor);	// 콜리전에 닿은 액터가 주인공 케릭터여야 함
	if (Character)
	{
		// 레벨을 이동시킴
		UGameplayStatics::OpenLevel(GetWorld(),FName(TransferLevelName));
	}
}