#include "LevelStreamerActor.h"

ALevelStreamerActor::ALevelStreamerActor()
{

	CHelpers::CreateComponent<UBoxComponent>(this, &OverlapVolume, "OverlapVolume", RootComponent);

	OverlapVolume->OnComponentBeginOverlap.AddUniqueDynamic(this, &ALevelStreamerActor::OverlapBegins);		// �� �ε� �Լ��� �ڽ��ݸ����� begin �������Լ��� ���ε�
	OverlapVolume->OnComponentEndOverlap.AddUniqueDynamic(this, &ALevelStreamerActor::OverlapEnds);		// ��ε� �Լ��� end ������ �Լ��� ���ε�

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