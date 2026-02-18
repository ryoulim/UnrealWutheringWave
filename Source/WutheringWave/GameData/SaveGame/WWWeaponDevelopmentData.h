// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "WWSaveGameBase.h"
#include "Headers/WWEnums.h"
#include "WWWeaponDevelopmentData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FWWWeaponDevelopmentData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = System)
	int32 WeaponID{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Development)
	int32 EquipCharacterID{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Development)
	int32 Level{1};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Development)
	int32 Ascension{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Development)
	float Exp{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Development)
	int32 ResonanceChain{};
};

UCLASS()
class WUTHERINGWAVE_API UWWWeaponDevelopmentSaveGame : public UWWSaveGameBase
{
	GENERATED_BODY()

public:
	void AddWeapon(int32 WeaponID);
	int32 AddDefaultWeapon(EWWWeaponTypeName WeaponType, int32 EquipCharacterID);

private:
	int32 FindEmptySlot();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UserData)
	TMap<int32, FWWWeaponDevelopmentData> WeaponMap;
};