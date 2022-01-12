
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
		int B = 20;	// 배치된 액터들이 값을 따로 가질 때 (EditInstanceOnly)

	UPROPERTY(EditDefaultsOnly)
		int C;	// 배치된 모든 액터의 값이 공통으로 들어가야 할 때 사용 (EditDefaultsOnly)

	UPROPERTY(VisibleAnywhere)
		int Test = 20;	// 수정불가, 값 확인만 가능

protected:
	// 블루프린트에 접근하는 변수는 private일 때 접근 불가임. 무조건 protected로 만들어줘야 함
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int Test1 = 15;		

public:	
	AC01_Property();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
