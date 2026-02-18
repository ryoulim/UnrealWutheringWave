// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WWSaveGameBase.h"
#include "WWInventoryData.generated.h"

/**
 *
 */
UCLASS()
class WUTHERINGWAVE_API UWWWWInventoryDataSaveGame : public UWWSaveGameBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UserData)
	int32 Money{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UserData)
	TMap<int32, int32> ItemMap;
};