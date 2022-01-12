#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C03_Spawner.generated.h"

UCLASS()
class UONLINE_CPP_API AC03_Spawner : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AC02_SpawnActor> SpawnClass[3];	// AC02_SpawnActor에서만 상속받은 클래스 이하로만 제한해서 사용 가능
	// 리플렉션: 자료형의 타입을 변수로 다룰 수 있도록 해주는 기능
	// 스폰시킬 것이 box, cone, sphere이기 때문에 배열로 선언
	// 스폰될 클래스타입을 지정


public:	
	AC03_Spawner();

protected:
	virtual void BeginPlay() override;

private:
	// 스폰된 결과를 저장할 클래스
	class AC02_SpawnActor* SpawnActors[3];

};
