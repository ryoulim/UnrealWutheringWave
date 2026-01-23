// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */

#define WWPRINTF(Format, ...) \
if (GEngine) \
{ \
    GEngine->AddOnScreenDebugMessage( \
        -1, 0.f, FColor::Green, \
        FString::Printf(Format, ##__VA_ARGS__) \
    ); \
}

#define WWDECLARE_DATAASSET_INT32(ClassName, AssetTypeName) \
static FPrimaryAssetId GetID(int32 InID) \
{ \
return FPrimaryAssetId(FPrimaryAssetType(TEXT(#AssetTypeName)), FName(*FString::FromInt(InID))); \
} \
static const ClassName* Get(int32 InID) \
{ \
	return Cast<ClassName>(UAssetManager::Get().GetPrimaryAssetObject(GetID(InID))); \
} \
virtual FPrimaryAssetId GetPrimaryAssetId() const override \
{ \
	return GetID(ID); \
}

#define WWDECLARE_DATAASSET_ENUM(ClassName, AssetTypeName, IDType) \
static FPrimaryAssetId GetID(IDType InID) \
{ \
return FPrimaryAssetId(FPrimaryAssetType(TEXT(#AssetTypeName)), FName(*StaticEnum<IDType>()->GetNameStringByValue(static_cast<int64>(InID)))); \
} \
static const ClassName* Get(IDType InID) \
{ \
	return Cast<ClassName>(UAssetManager::Get().GetPrimaryAssetObject(GetID(InID))); \
} \
virtual FPrimaryAssetId GetPrimaryAssetId() const override \
{ \
	return GetID(ID); \
}