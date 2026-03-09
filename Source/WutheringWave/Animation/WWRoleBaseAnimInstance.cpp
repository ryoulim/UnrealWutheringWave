// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/WWRoleBaseAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interface/WWInputStateCheckInterface.h"

#include "Headers/WWMacros.h"

UWWRoleBaseAnimInstance::UWWRoleBaseAnimInstance()
{
	MovingThreshold = 3.f;
	JumpingThreshold = 100.f;
}

bool UWWRoleBaseAnimInstance::IsMoveTriggerdThisFrame()
{
	// 멀티플레이어 환경에서는 내 로컬 컨트롤러의 입력을 참조하면 안 됩니다.
	// 폰 자체의 가속도나 이동 속도를 기준으로 판단해야 합니다.
	if (Movement)
	{
		// 가속도 크기나 GroundSpeed로 현재 이동 의도를 파악
		return Movement->GetCurrentAcceleration().SizeSquared() > 0.1f || GroundSpeed > MovingThreshold;
	}
	return false;
}

void UWWRoleBaseAnimInstance::SetStopMode()
{
	if (bIsLastLandFootRight)
	{
		if (MoveState > 1.95f)
		{
			StopMode = EWBaseAnimStopMode::SprintR;
		}
		else if (MoveState > 0.95f)
		{
			StopMode = EWBaseAnimStopMode::RunR;
		}
		else
		{
			StopMode = EWBaseAnimStopMode::WalkR;
		}
	}
	else
	{
		if (MoveState > 1.95f)
		{
			StopMode = EWBaseAnimStopMode::SprintL;
		}
		else if (MoveState > 0.95f)
		{
			StopMode = EWBaseAnimStopMode::RunL;
		}
		else
		{
			StopMode = EWBaseAnimStopMode::WalkL;
		}

	}
}

void UWWRoleBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}

}

void UWWRoleBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D();
		bIsIdle = GroundSpeed < MovingThreshold;
		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshold);
	}
	//WWPRINTF(TEXT("GoundSpeed : %.2f"), GroundSpeed);
}

inline void UWWRoleBaseAnimInstance::RightFootLand()
{
	bIsLastLandFootRight = true;
	//SetStopMode();
	//WWPRINTF(TEXT("RightFootLand"));
}

inline void UWWRoleBaseAnimInstance::LeftFootLand()
{
	bIsLastLandFootRight = false;
	//SetStopMode();
	//WWPRINTF(TEXT("LeftFootLand"));
}
