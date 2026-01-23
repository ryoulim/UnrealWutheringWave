// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SlideWidget/WWSlideWidget.h"
#include "WWRoleSlideWidget.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVE_API UWWRoleSlideWidget : public UWWSlideWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = UI)
	float ItemHeight = 100.f;

	UPROPERTY(EditAnywhere, Category = UI)
	float ItemSpacing = 30.f;

    virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetButtonImage();
};
