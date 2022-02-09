#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "C_FPSHUD.generated.h"

UCLASS()
class FPS_BEGIN_API AC_FPSHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
		UTexture2D* CrosshairTexture;

public:
	virtual void DrawHUD() override;

};
