// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SlideWidget/WWButtonInSlideWidget.h"
#include "Headers/WWEnums.h"
#include "WWRoleDevelopHeadWidget.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVE_API UWWRoleDevelopHeadWidget : public UWWButtonInSlideWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Icon)
	void SetRoleImage(int32 InCharacterName);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> RoleImage;
};
