// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Interface/WWFootLandCheckInterface.h"
#include "WWRoleBaseAnimInstance.generated.h"

UENUM(Blueprinttype)
enum class EWBaseAnimStopMode : uint8
{
	WalkL,
	WalkR,
	RunL,
	RunR,
	SprintL,
	SprintR
};

/**
 *
 */
UCLASS()
class WUTHERINGWAVE_API UWWRoleBaseAnimInstance : public UAnimInstance, public IWWFootLandCheckInterface
{
	GENERATED_BODY()

public:
	UWWRoleBaseAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	/* Foot Land Check */
public:
	virtual void RightFootLand() override;
	virtual void LeftFootLand() override;

	/* Utility */
public:
	UFUNCTION(BlueprintCallable)
	bool IsMoveTriggerdThisFrame();

	UFUNCTION(BlueprintCallable)
	void SetStopMode();

	/* 기본 변수들 */
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class ACharacter> Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class UCharacterMovementComponent> Movement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsIdle : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float MovingThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsFalling : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsJumping : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float JumpingThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	bool bIsLastLandFootRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	EWBaseAnimStopMode StopMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	float MoveState = 1; // 0 : walk, 1 : Run, 2 : Sprint

	/* 스테이트 조정 */
public:
	void OnMoveCall() { bMoveCall = true; }
	void OnDashCall() { bDashCall = true; }
	void OnNormalAttackCallCall() { bNormalAttackCall = true; }
	void OnSpecialAttackCall() { bSpecialAttackCall = true; }
	void OnEcoAttackCall() { bEcoAttackCall = true; }
	void OnUltimateAttackCall() { bUltimateAttackCall = true; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StateCall)
	bool bMoveCall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StateCall)
	bool bDashCall;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StateCall)
	bool bNormalAttackCall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StateCall)
	bool bSpecialAttackCall;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StateCall)
	bool bEcoAttackCall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StateCall)
	bool bUltimateAttackCall;
};
