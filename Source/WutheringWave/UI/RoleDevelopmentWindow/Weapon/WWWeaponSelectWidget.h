// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SlideWidget/WWSlideWidget.h"
#include "Headers/WWEnums.h"
#include "WWWeaponSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVE_API UWWWeaponSelectWidget : public UWWSlideWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct();

public:
	UFUNCTION(BlueprintCallable)
	void UpdateWindowbyType(EWWWeaponTypeName InType);

protected:
	virtual void CheckButtons(const FVector2D& InMousePosition) override;

	UPROPERTY(EditAnywhere, Category = "Setting|UI")
	float ItemSize = 100.f;

	UPROPERTY(EditAnywhere, Category = "Setting|UI")
	float ItemSpacing = 30.f;

	UPROPERTY(BlueprintReadOnly, Category = UI)
	TArray<TObjectPtr<class UWWWeaponSelectButton>> ActiveButtons{};
};
