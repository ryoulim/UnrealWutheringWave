// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/AssetManager.h"
#include "Headers/WWMacros.h"
#include "WWWeaponDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVE_API UWWWeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	WWDECLARE_DATAASSET_INT32(UWWWeaponDataAsset, Weapon)
	UPROPERTY(EditDefaultsOnly, Category = "ID")
	int32 ID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI", meta = (AssetBundles = "UITexture"))
	TSoftObjectPtr<class UTexture2D> UITexture;
};
