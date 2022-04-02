#pragma once

//#include "CoreMinimal.h"
//#include "EngineMinimal.h"	// 엔진 클래스의 선언을 모아둔 헤더, ArenaBattle.h 에서 공동 선언
#include "ArenaBattle.h"
#include "GameFramework/Actor.h"

#include "Fountain.generated.h"

UCLASS()
class ARENABATTLE_API AFountain : public AActor
{
	GENERATED_BODY()

private:
	// AllowPrivateAccess를 붙여 Private 변수임에도 에디터상에서 편집 가능함
	UPROPERTY(EditAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
		float RotateSpeed;
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PostInitializeComponents() override;

public:	
	AFountain();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Water;

	UPROPERTY(VisibleAnywhere)
	UPointLightComponent* Light;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* Splash;

	UPROPERTY(EditAnyWhere, Category = "ID")
		int32 ID;

};
