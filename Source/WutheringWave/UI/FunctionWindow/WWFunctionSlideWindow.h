// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SlideWidget/WWSlideWidget.h"
#include "WWFunctionSlideWindow.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVE_API UWWFunctionSlideWindow : public UWWSlideWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void Appear();

	UFUNCTION(BlueprintCallable)
	void Disappear();

private:
	void UpdateAppear(float DeltaTime);

protected:
	bool bIsAppear = {};
	float AppearTimeAcc = {};
	int32 LastAppearButtonIndex = {};

	UPROPERTY(EditDefaultsOnly, Category = Setting)
	float ButtonAppearInterval = { 0.03f };
};
