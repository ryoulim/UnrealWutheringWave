// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Headers/WWEnums.h"
#include "WWDataTableBase.h"
#include "WWCharacterStatTable.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FWWCharacterStatTable : public FWWDataTableBase
{
	GENERATED_BODY()

	/* Visual Stat */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VisualStat)
	FString CharacterName_Ko;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VisualStat)
	EWWElementName ElementType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VisualStat)
	EWWWeaponTypeName WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VisualStat)
	float AttackRange = { 1.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VisualStat)
	float AttackSpeed = { 1.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VisualStat)
	float MovementSpeed = { 1.f };

	/* Base Stat */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BaseStat)
	float MaxHp = { 1.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BaseStat)
	float Attack = { 1.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BaseStat)
	float Defense = { 1.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BaseStat)
	float EnergyRegen = { 1.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BaseStat)
	float CritRate = { 1.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BaseStat)
	float CritDamage = { 1.f };

	/* Growth Stat */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GrowthStat)
	float MaxHpPerLV = { 1.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GrowthStat)
	float AttackPerLV = { 1.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GrowthStat)
	float DefensePerLV = { 1.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GrowthStat)
	float EnergyRegenPerLV = { 1.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GrowthStat)
	float CritRatePerLV = { 1.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GrowthStat)
	float CritDamagePerLV = { 1.f };
};
