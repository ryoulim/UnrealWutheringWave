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
	if (auto PC = Cast<IWWInputStateCheckInterface>(GetWorld()->GetFirstPlayerController()))
	{
		return PC->IsMoveTriggerdThisFrame();
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
