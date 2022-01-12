
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C01_Property.generated.h"

UCLASS()
class UONLINE_CPP_API AC01_Property : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		int A = 10;

	UPROPERTY(EditInstanceOnly)
		int B = 20;	// ��ġ�� ���͵��� ���� ���� ���� �� (EditInstanceOnly)

	UPROPERTY(EditDefaultsOnly)
		int C;	// ��ġ�� ��� ������ ���� �������� ���� �� �� ��� (EditDefaultsOnly)

	UPROPERTY(VisibleAnywhere)
		int Test = 20;	// �����Ұ�, �� Ȯ�θ� ����

protected:
	// �������Ʈ�� �����ϴ� ������ private�� �� ���� �Ұ���. ������ protected�� �������� ��
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int Test1 = 15;		

public:	
	AC01_Property();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
