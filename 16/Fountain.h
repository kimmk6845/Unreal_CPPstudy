#pragma once

//#include "CoreMinimal.h"
//#include "EngineMinimal.h"	// ���� Ŭ������ ������ ��Ƶ� ���, ArenaBattle.h ���� ���� ����
#include "ArenaBattle.h"
#include "GameFramework/Actor.h"

#include "Fountain.generated.h"

UCLASS()
class ARENABATTLE_API AFountain : public AActor
{
	GENERATED_BODY()

private:
	// AllowPrivateAccess�� �ٿ� Private �����ӿ��� �����ͻ󿡼� ���� ������
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
