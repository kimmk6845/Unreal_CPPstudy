#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_SpawnActor.generated.h"

UCLASS()
class UONLINE_CPP_API AC02_SpawnActor : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;	// 컴포넌트 변수에는 VisibleDefaultsOnly
	
public:	
	AC02_SpawnActor();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void ChangeColor();

private:
	class UMaterialInstanceDynamic* Material;

};
