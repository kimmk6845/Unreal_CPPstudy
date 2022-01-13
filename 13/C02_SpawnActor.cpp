#include "C02_SpawnActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

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
	
	////// ConstructorHelpers는 생성자에서만 사용 가능하므로 여기서는 사용 불가]
	////// 따라서, 게임 상에서 동적으로 에셋을 로딩하기 위해 StaticLoadObject를 사용함
	////머티리얼 경로 = MaterialInstanceConstant'/Game/Materials/M_Mesh_Inst.M_Mesh_Inst'
	//UObject* obj = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), NULL, L"MaterialInstanceConstant'/Game/Materials/M_Mesh_Inst.M_Mesh_Inst'");
	//UMaterialInstanceConstant* material = Cast<UMaterialInstanceConstant>(obj);

	// CHelpers 이용
	// 동적으로 머티리얼을 부름
	UMaterialInstanceConstant* material;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/Materials/M_Mesh_Inst.M_Mesh_Inst'");
	// 다이나믹 머티리얼 생성
	Material = UMaterialInstanceDynamic::Create(material, this);
	Mesh->SetMaterial(0, Material);

	UKismetSystemLibrary::K2_SetTimer(this, "ChangeColor", 1.0f, true);	// ChangeColor를 1초마다 실행시키면서 반복

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