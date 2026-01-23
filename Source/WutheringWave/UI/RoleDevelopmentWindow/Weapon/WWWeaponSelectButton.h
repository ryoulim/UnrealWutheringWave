// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SlideWidget/WWButtonInSlideWidget.h"
#include "Headers/WWEnums.h"
#include "WWWeaponSelectButton.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVE_API UWWWeaponSelectButton : public UWWButtonInSlideWidget
{
	GENERATED_BODY()

public:
	void SetImage(int32 WeaponID);
	EWWWeaponTypeName GetWeapontype() {
		return WeaponType;
	}

protected:
	EWWWeaponTypeName WeaponType{};

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> WeaponImage;
};
