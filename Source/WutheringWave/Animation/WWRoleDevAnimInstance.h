// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <atomic>
#include "Headers/WWEnums.h"
#include "Animation/AnimInstance.h"
#include "WutheringWave/GameData/DataAsset/WWRoleDataAsset.h"
#include "WWRoleDevAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVE_API UWWRoleDevAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	void ReadyAnimSet(const TMap<EWWUIAnimName, FWWUIAnimSet>& InAnimSets);

	/* 아토믹 */
public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void SetTargetAnim(EWWUIAnimName InTargetAnim)
	{
		TargetAnim = InTargetAnim;
	}
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	EWWUIAnimName GetTargetAnim() const
	{
		return TargetAnim;
	}
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void SetReStartAnim(bool InReStartAnim)
	{
		bReStartAnim = InReStartAnim;
	}
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	bool GetReStartAnim() const
	{
		return bReStartAnim;
	}

protected:
	std::atomic<EWWUIAnimName> TargetAnim{};
	std::atomic<bool> bReStartAnim{};

	/* Anim Graph용 */
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<const UAnimSequence> NatureStartAnim{};

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<const UAnimSequence> NatureLoopAnim{};

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<const UAnimSequence> NatureEndAnim{};

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<const UAnimSequence> WeaponStartAnim{};

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<const UAnimSequence> WeaponLoopAnim{};

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<const UAnimSequence> WeaponEndAnim{};

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<const UAnimSequence> ResonantStartAnim{};

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<const UAnimSequence> ResonantLoopAnim{};

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<const UAnimSequence> ResonantEndAnim{};

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<const UAnimSequence> ChipStartAnim{};

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<const UAnimSequence> ChipLoopAnim{};

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<const UAnimSequence> ChipEndAnim{};
};
