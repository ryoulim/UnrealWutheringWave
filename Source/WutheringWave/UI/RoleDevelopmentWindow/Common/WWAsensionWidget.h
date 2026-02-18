// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WWAsensionWidget.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVE_API UWWAsensionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateWindow(int32 InAscensionLevel);
	void UpdateWindow_Implementation(int32 InAscensionLevel);
};
