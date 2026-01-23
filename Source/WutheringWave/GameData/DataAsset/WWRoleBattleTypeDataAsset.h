// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Headers/WWEnums.h"
#include "Engine/AssetManager.h"
#include "Headers/WWMacros.h"
#include "WWRoleBattleTypeDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVE_API UWWRoleBattleTypeDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	WWDECLARE_DATAASSET_ENUM(UWWRoleBattleTypeDataAsset, RoleBattleSytle, EWWRoleBattleTypeName)

	UPROPERTY(EditDefaultsOnly, Category = "ID")
	EWWRoleBattleTypeName ID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AssetBundles = "Default"))
	TSoftObjectPtr<class UPaperSprite> DefaultIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Name_Ko;
};
