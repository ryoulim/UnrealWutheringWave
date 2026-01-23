// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WWEnums.generated.h"

/**
 *
 */

UENUM(BlueprintType)
enum class EWWUIAnimName : uint8
{
	Chip,
	Nature,
	Resonant,
	Weapon
};

UENUM(BlueprintType)
enum class EWWElementName : uint8
{
	Zero,
	Fire,
	Ice,
	Wind,
	Thunder,
	Light,
	Dark
};

UENUM(BlueprintType)
enum class EWWStatName : uint8
{
	HP,
	Attack,
	Defense,
	EnergyRegen,
	CritRate,
	CritDamage
};

UENUM(Blueprinttype)
enum class EWWRoleBattleTypeName : uint8
{
	SupportAndHealer,
	MainDamageDealer,
	ConcertoEfficiency,
	BasicAttackDMG,
	HeavyAttackDMG,
	ResonanceSkillDMG,
	ResonanceLiberationDamage,
	Traction,
	CoordinatedAttack,
	Stagnation,
	ResonanceLiberationRegeneration,
	VibrationStrengthReduction,
	InterruptionResistanceBoost,
	DMGAmplification,
	HavocDMGAmplification,
	AeroDMGAmplification,
	ElectroDMGAmplification,
	FusionDMGAmplification,
	GlacioDMGAmplification,
	SpectroDMGAmplification,
	BasicAttackDMGAmplification,
	HeavyAttackDMGAmplification,
	ResonanceSkillDMGAmplification,
	ResonanceLiberationDMGAmplification,
	EchoSkillDMGAmplification,
	CoordinatedAttackDMGAmplification,
	AeroErosion,
	ElectroFlare,
	GlacioChafe,
	FusionBurst,
	SpectroFrazzle,
	HavocBane,
	TuneRuptureResponse,
	TuneStrainResponse,
	TuneBreakBoost,
};

UENUM(Blueprinttype)
enum class EWWWeaponTypeName : uint8
{
	Sword,
	Broadblade,
	Pistols,
	Rectifier,
	Gauntlets
};