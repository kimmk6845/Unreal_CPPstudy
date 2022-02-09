#include "C_FPSProjectile.h"
#include "Global.h"
#include "Sound/SoundCue.h"


AC_FPSProjectile::AC_FPSProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	//CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	//CollisionComponent->InitSphereRadius(15.0f);
	//RootComponent = CollisionComponent;

	CHelpers::CreateComponent<USphereComponent>(this, &CollisionComponent, "SphereComponent", RootComponent);
	CollisionComponent->InitSphereRadius(15.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	CollisionComponent->OnComponentHit.AddDynamic(this, &AC_FPSProjectile::OnHit);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	//CHelpers::CreateComponent<UProjectileMovementComponent>(this, &ProjectileMovementComponent, "ProjectileMovementComponent");
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 20000.0f;
	ProjectileMovementComponent->MaxSpeed = 20000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;

	//// 너무 튕김
	//ProjectileMovementComponent->bShouldBounce = true;
	//ProjectileMovementComponent->Bounciness = 0.3f;

	InitialLifeSpan = 3.0f;		// 수명

	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Bullet", CollisionComponent);
	Mesh->SetRelativeScale3D(FVector(0.07f));

	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Asset/Sphere.Sphere'");
	Mesh->SetStaticMesh(mesh);


}

void AC_FPSProjectile::BeginPlay()
{
	Super::BeginPlay();

}

void AC_FPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// 발사 처리 함수
void AC_FPSProjectile::FireInDirection(const FVector& ShootDirection)
{
	UGameplayStatics::PlaySound2D(this, shot);

	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AC_FPSProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NotmalImpulse, const FHitResult& Hit)
{
	//// 발사체에 맞은 액터의 힘을 가해 날아감
	//if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	//{
	//	OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 0.001f, Hit.ImpactPoint);
	//}
}

void AC_FPSProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->IsA(AActor::StaticClass()) && OtherActor->ActorHasTag("Enemy"))
	{
		UGameplayStatics::ApplyDamage(OtherActor, FMath::RandRange(25.0f, 50.0f), NULL, this, UDamageType::StaticClass());
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Apply Damage!!"));

		this->Destroy();
	}

	// 벽 뚫고 적을 맞추는 버그 방지
	if (OtherActor->IsA(AActor::StaticClass()) && !OtherActor->ActorHasTag("User"))
		this->Destroy();
}
