// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WWWindowBaseWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWWWindowBaseCloseCall);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWWWindowBaseLoadEnd);

/**
 * 
 */
UCLASS()
class WUTHERINGWAVE_API UWWWindowBaseWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

public:
	virtual void Appear() {}
	FOnWWWindowBaseCloseCall OnWWWindowBaseCloseCall;
	FOnWWWindowBaseLoadEnd OnWWWindowBaseLoadEnd;
};