#include "C02_SpawnActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"

AC02_SpawnActor::AC02_SpawnActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	////StaticMesh'/Game/Meshs/M_Cube.M_Cube'		�տ��� U�� ���̸� �ڷ���, �ڿ��� ���� ���
	//ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(L"StaticMesh'/Game/Meshs/M_Cube.M_Cube'");	// TEXT�� �����ڵ� L�� ��Ƽ����Ʈ (unreal�� TEXT�� ���°��� ����)
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

