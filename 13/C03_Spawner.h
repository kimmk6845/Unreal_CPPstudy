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
		TSubclassOf<class AC02_SpawnActor> SpawnClass[3];	// AC02_SpawnActor������ ��ӹ��� Ŭ���� ���Ϸθ� �����ؼ� ��� ����
	// ���÷���: �ڷ����� Ÿ���� ������ �ٷ� �� �ֵ��� ���ִ� ���
	// ������ų ���� box, cone, sphere�̱� ������ �迭�� ����
	// ������ Ŭ����Ÿ���� ����


public:	
	AC03_Spawner();

protected:
	virtual void BeginPlay() override;

private:
	// ������ ����� ������ Ŭ����
	class AC02_SpawnActor* SpawnActors[3];

};
