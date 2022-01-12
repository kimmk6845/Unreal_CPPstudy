#include "C03_Spawner.h"
#include "Global.h"
#include "C02_SpawnActor.h"

AC03_Spawner::AC03_Spawner()
{

}

void AC03_Spawner::BeginPlay()
{
	Super::BeginPlay();

	for (int32 i = 0; i < 3; i++)
	{
		//// 스폰 후 위치 조정
		//FTransform transform;
		//SpawnActors[i] = GetWorld()->SpawnActor<AC02_SpawnActor>(SpawnClass[i], transform);	// 생성

		//FVector location = GetActorLocation();
		//SpawnActors[i]->SetActorLocation(FVector(location.X + i * 400, location.Y, location.Z));	// 이동


		// 생성과 동시에 위치 설정
		FTransform transform;
		FVector location = GetActorLocation();

		transform.SetLocation(FVector(location.X + i * 400, location.Y, location.Z));
		SpawnActors[i] = GetWorld()->SpawnActor<AC02_SpawnActor>(SpawnClass[i], transform);


		
	}
	
}
