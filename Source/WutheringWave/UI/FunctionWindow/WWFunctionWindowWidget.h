// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Common/WWWindowBaseWidget.h"
#include "WWFunctionWindowWidget.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVE_API UWWFunctionWindowWidget : public UWWWindowBaseWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void Appear() override;
	void DisAppearButton(); 

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> NameTextBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> UIDTextBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> BirthDayTextBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> RankTextBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> LevelTextBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> ExpTextBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UMultiLineEditableTextBox> UserWordTextBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UWWFunctionSlideWindow> ButtonSlideWidget;
};