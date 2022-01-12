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
		//// ���� �� ��ġ ����
		//FTransform transform;
		//SpawnActors[i] = GetWorld()->SpawnActor<AC02_SpawnActor>(SpawnClass[i], transform);	// ����

		//FVector location = GetActorLocation();
		//SpawnActors[i]->SetActorLocation(FVector(location.X + i * 400, location.Y, location.Z));	// �̵�


		// ������ ���ÿ� ��ġ ����
		FTransform transform;
		FVector location = GetActorLocation();

		transform.SetLocation(FVector(location.X + i * 400, location.Y, location.Z));
		SpawnActors[i] = GetWorld()->SpawnActor<AC02_SpawnActor>(SpawnClass[i], transform);


		
	}
	
}
