#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "FPSCharacter.h"

#include "LevelStreamerActor.generated.h"

UCLASS()
class P2022_API ALevelStreamerActor : public AActor
{
	GENERATED_BODY()
	
private:	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = true))
		UBoxComponent* OverlapVolume;


protected:
	UPROPERTY(EditAnywhere)
		FName LevelToLoad;	// 로드할 맵 이름 받는 FName변수

	UFUNCTION()
		void OverlapBegins(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OverlapEnds(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:	
	ALevelStreamerActor();
};
