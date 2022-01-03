// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawnMovementComponent.h"

void UCollidingPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // PawnOwner: 이 컴포넌트를 소유하고 있는 폰
    // UpdatedComponent: 이동시키고 업데이트해야 할 컴포넌트
    // ShouldSkipUpdate: 이동된 컴포넌트가 이동할 수 없거나 렌더링 되지 않은 경우인지 판별해 알려주는 함수
    if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))     // 무브먼트 컴포넌트가 이동가능한 상태인지 확인
    {
        return;
    }

    // ConsumeInputVector: 입력된 이동 벡터를 가져옴
    FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.0f;
    if (!DesiredMovementThisFrame.IsNearlyZero())
    {
        FHitResult Hit;
        // Unreal 피직스를 이용해 장애물을 피해 폰 무브먼트 컴포넌트를 이동시켜 줌
        SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

        if (Hit.IsValidBlockingHit())   // 충돌이 발생하면
        {
            // 충돌체의 표면을 타고 미끄러지듯이 이동
            SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
        }
    }
}