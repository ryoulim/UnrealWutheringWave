// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WWRoleDevLevelWidget.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVE_API UWWRoleDevLevelWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateWindow(int32 InCurrentLevel, int32 InMaxLevel);
	void UpdateWindow_Implementation(int32 InCurrentLevel, int32 InMaxLevel);
};
