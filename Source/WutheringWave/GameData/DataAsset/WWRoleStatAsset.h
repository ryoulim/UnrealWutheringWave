// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/AssetManager.h"
#include "Headers/WWEnums.h"
#include "Headers/WWMacros.h"
#include "WWRoleStatAsset.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FStatInformation
{
	GENERATED_BODY()


};

UCLASS()
class WUTHERINGWAVE_API UWWRoleStatAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	WWDECLARE_DATAASSET_ENUM(UWWRoleStatAsset, RoleStat, EWWStatName)
	UPROPERTY(EditDefaultsOnly, Category = "ID")
	EWWStatName ID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AssetBundles = "Default"))
	TSoftObjectPtr<class UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Name_Ko;
};
