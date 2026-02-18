// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Headers/WWEnums.h"
#include "WWButtonInSlideWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRoleHeadButtonClicked, int32, ButtonID);

/**
 * 
 */
UCLASS(Abstract)
class WUTHERINGWAVE_API UWWButtonInSlideWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Icon)
	void CheckButton(const FVector2D& ScreenMousePos);

	int32 GetButtonID()
	{
		return ButtonID;
	}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting")
	int32 ButtonID{};

	UPROPERTY(BlueprintAssignable)
	FOnRoleHeadButtonClicked OnButtonClicked{};
};
