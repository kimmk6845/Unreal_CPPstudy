#include "LevelStreamerActor.h"

ALevelStreamerActor::ALevelStreamerActor()
{

	CHelpers::CreateComponent<UBoxComponent>(this, &OverlapVolume, "OverlapVolume", RootComponent);

	OverlapVolume->OnComponentBeginOverlap.AddUniqueDynamic(this, &ALevelStreamerActor::OverlapBegins);		// 맵 로드 함수를 박스콜리전의 begin 오버랩함수에 바인딩
	OverlapVolume->OnComponentEndOverlap.AddUniqueDynamic(this, &ALevelStreamerActor::OverlapEnds);		// 언로드 함수를 end 오버랩 함수에 바인딩

}

void ALevelStreamerActor::OverlapBegins(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (LevelToLoad != "" && OtherActor == MyCharacter)
	{
		FLatentActionInfo LatentInfo;
		UGameplayStatics::LoadStreamLevel(this, LevelToLoad, true, true, LatentInfo);
	}
}

void ALevelStreamerActor::OverlapEnds(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (LevelToLoad != "" && OtherActor == MyCharacter)
	{
		FLatentActionInfo LatentInfo;
		UGameplayStatics::UnloadStreamLevel(this, LevelToLoad, LatentInfo, true);
	}
}