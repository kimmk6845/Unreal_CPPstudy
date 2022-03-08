#pragma once

#include "CoreMinimal.h"
#include "My/Interactable.h"
#include "Global.h"

#include "InteractDoor.generated.h"

UCLASS()
class P2022_API AInteractDoor : public AInteractable
{
	GENERATED_BODY()
		
private:
	bool bOpen;

public:
	AInteractDoor();

	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact_Implementation() override;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* DoorFrame;
};
