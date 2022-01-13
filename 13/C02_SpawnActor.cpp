#include "C02_SpawnActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

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
	
	////// ConstructorHelpers�� �����ڿ����� ��� �����ϹǷ� ���⼭�� ��� �Ұ�]
	////// ����, ���� �󿡼� �������� ������ �ε��ϱ� ���� StaticLoadObject�� �����
	////��Ƽ���� ��� = MaterialInstanceConstant'/Game/Materials/M_Mesh_Inst.M_Mesh_Inst'
	//UObject* obj = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), NULL, L"MaterialInstanceConstant'/Game/Materials/M_Mesh_Inst.M_Mesh_Inst'");
	//UMaterialInstanceConstant* material = Cast<UMaterialInstanceConstant>(obj);

	// CHelpers �̿�
	// �������� ��Ƽ������ �θ�
	UMaterialInstanceConstant* material;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/Materials/M_Mesh_Inst.M_Mesh_Inst'");
	// ���̳��� ��Ƽ���� ����
	Material = UMaterialInstanceDynamic::Create(material, this);
	Mesh->SetMaterial(0, Material);

	UKismetSystemLibrary::K2_SetTimer(this, "ChangeColor", 1.0f, true);	// ChangeColor�� 1�ʸ��� �����Ű�鼭 �ݺ�

}

void AC02_SpawnActor::ChangeColor()
{
	FLinearColor color;
	color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.A = 1.0f;

	Material->SetVectorParameterValue("Color", color);

}