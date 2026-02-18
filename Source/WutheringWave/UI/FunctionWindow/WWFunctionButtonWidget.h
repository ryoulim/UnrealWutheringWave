// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SlideWidget/WWButtonInSlideWidget.h"
#include "WWFunctionButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVE_API UWWFunctionButtonWidget : public UWWButtonInSlideWidget
{
	GENERATED_BODY()

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void SetAppear(bool InAppear);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class URetainerBox> FlipRetainerBox;

	bool bIsAppear = { false };
	float AppearTimeAcc = {};

	UPROPERTY(EditDefaultsOnly, Category = Setting)
	float Duration = { 0.2f };
};
