#include "C02_SpawnActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"

AC02_SpawnActor::AC02_SpawnActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	////StaticMesh'/Game/Meshs/M_Cube.M_Cube'		앞에는 U를 붙이면 자료형, 뒤에는 절대 경로
	//ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(L"StaticMesh'/Game/Meshs/M_Cube.M_Cube'");	// TEXT는 유니코드 L은 멀티바이트 (unreal은 TEXT를 쓰는것이 정석)
	//if (mesh.Succeeded())
	//	Mesh->SetStaticMesh(mesh.Object);

	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshs/M_Cube.M_Cube'");
	Mesh->SetStaticMesh(mesh);

}

void AC02_SpawnActor::BeginPlay()
{
	Super::BeginPlay();
	
}

