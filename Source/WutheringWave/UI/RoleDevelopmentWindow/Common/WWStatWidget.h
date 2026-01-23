// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Headers/WWEnums.h"
#include "WWStatWidget.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVE_API UWWStatWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintCallable)
	void UpdateView(EWWStatName StatName, float Value, bool isPercent);
	UFUNCTION(BlueprintCallable)
	void UpdateValue(int32 Level, float BaseValue, float ValuePerLv);
	UFUNCTION(BlueprintCallable)
	float CalcValue(int32 Level, float BaseValue, float ValuePerLv);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
	EWWStatName StatType{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
	float StatValue{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
	bool bIsPercent{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
	bool bActiveBG{};

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UImage> BackGround;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UImage> StatIcon;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> StatNameText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> StatValueText;
};
