// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/AssetManager.h"
#include "Headers/WWEnums.h"
#include "Headers/WWMacros.h"
#include "WWWeaponTypeDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVE_API UWWWeaponTypeDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	WWDECLARE_DATAASSET_ENUM(UWWWeaponTypeDataAsset, WeaponType, EWWWeaponTypeName)
	UPROPERTY(EditDefaultsOnly, Category = "ID")
	EWWWeaponTypeName ID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AssetBundles = "Default"))
	TSoftObjectPtr<class UTexture2D> DefaultIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 DefaultWeaponID{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Name_Ko;
};
