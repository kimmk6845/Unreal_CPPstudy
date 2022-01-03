// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawnMovementComponent.h"

void UCollidingPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // PawnOwner: �� ������Ʈ�� �����ϰ� �ִ� ��
    // UpdatedComponent: �̵���Ű�� ������Ʈ�ؾ� �� ������Ʈ
    // ShouldSkipUpdate: �̵��� ������Ʈ�� �̵��� �� ���ų� ������ ���� ���� ������� �Ǻ��� �˷��ִ� �Լ�
    if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))     // �����Ʈ ������Ʈ�� �̵������� �������� Ȯ��
    {
        return;
    }

    // ConsumeInputVector: �Էµ� �̵� ���͸� ������
    FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.0f;
    if (!DesiredMovementThisFrame.IsNearlyZero())
    {
        FHitResult Hit;
        // Unreal �������� �̿��� ��ֹ��� ���� �� �����Ʈ ������Ʈ�� �̵����� ��
        SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

        if (Hit.IsValidBlockingHit())   // �浹�� �߻��ϸ�
        {
            // �浹ü�� ǥ���� Ÿ�� �̲��������� �̵�
            SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
        }
    }
}