// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/AssetManager.h"

#include "Headers/WWEnums.h"
#include "Headers/WWMacros.h"
#include "WWElementDataAsset.generated.h"

/**
 *
 */
UCLASS()
class WUTHERINGWAVE_API UWWElementDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	WWDECLARE_DATAASSET_ENUM(UWWElementDataAsset, Element, EWWElementName)
	UPROPERTY(EditDefaultsOnly, Category = "ID")
	EWWElementName ID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AssetBundles = "Default"))
	TSoftObjectPtr<class UTexture2D> DefaultIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AssetBundles = "Default"))
	TSoftObjectPtr<class UTexture2D> RoundIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Name_Ko;
};
