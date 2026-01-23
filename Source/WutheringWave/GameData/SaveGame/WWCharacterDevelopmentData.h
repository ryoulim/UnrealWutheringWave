// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WWSaveGameBase.h"
#include "WWCharacterDevelopmentData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FWWCharacterDevelopmentData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Development)
	int32 Level{1};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Development)
	int32 Ascension{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Development)
	float Exp{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SkillData)
	int32 ResonanceChain{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SkillData)
	int32 SkillLevel1{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SkillData)
	int32 SkillLevel2{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SkillData)
	int32 SkillLevel3{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SkillData)
	int32 SkillLevel4{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SkillData)
	int32 SkillLevel5{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = WeaponData)
	int32 EquipWeaponID{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EcoData)
	int32 EquipEco1ID{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EcoData)
	int32 EquipEco2ID{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EcoData)
	int32 EquipEco3ID{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EcoData)
	int32 EquipEco4ID{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EcoData)
	int32 EquipEco5ID{};
};

UCLASS()
class WUTHERINGWAVE_API UWWCharacterDevelopmentSaveGame : public UWWSaveGameBase
{
	GENERATED_BODY()

public:
	bool AddNewCharacter(int32 CharacterID, class UWWWeaponDevelopmentSaveGame* WeaponSaveGame);
	int32 GetSelectedCharatcterID() const;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UserData)
	TMap<int32, FWWCharacterDevelopmentData> CharacterMap;

	UPROPERTY()
	TArray<int32> PartyCharacter;

	UPROPERTY()
	int32 CurrentPartyIndex;
};