#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

UCLASS()
class P2022_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractable();

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintNativeEvent)
		void Interact();
	virtual void Interact_Implementation();

	UPROPERTY(EditAnywhere, Category = "Interact Properties")
		class UStaticMeshComponent* interactableMesh;
	UPROPERTY(EditAnywhere, Category = "Interact Properties")
		FString interactableHelpText;
};
