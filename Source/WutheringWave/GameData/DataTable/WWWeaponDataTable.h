// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WWDataTableBase.h"
#include "Headers/WWEnums.h"
#include "WWWeaponDataTable.generated.h"

/**
 *
 */

USTRUCT(BlueprintType)
struct FAscensionAbility
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AscensionGrowthStat1{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AscensionGrowthStat2{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AscensionGrowthStat3{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AscensionGrowthStat4{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AscensionGrowthStat5{};
};

USTRUCT(BlueprintType)
struct FWWWeaponDataTable : public FWWDataTableBase
{
	GENERATED_BODY()

	/* Information */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Information)
	EWWWeaponTypeName Type{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Information)
	FName Name_Ko{};

	/* MainStat1 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MainStat1)
	EWWStatName StatType1{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MainStat1)
	float BaseStat1{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MainStat1)
	float GrowthStat1{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MainStat1)
	bool isPercent1{};

	/* MainStat2 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MainStat2)
	EWWStatName StatType2{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MainStat2)
	float BaseStat2{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MainStat2)
	float GrowthStat2{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MainStat1)
	bool isPercent2{};

	/* Ascension */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ascension)
	TArray<FAscensionAbility> AscensionAbility;

	/* Description */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Description)
	FString SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Description)
	FString Description1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Description)
	FString Description2;
};
