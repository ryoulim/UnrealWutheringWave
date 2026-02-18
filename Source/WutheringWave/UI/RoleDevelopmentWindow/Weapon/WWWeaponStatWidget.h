// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WutheringWave/GameData/SaveGame/WWWeaponDevelopmentData.h"
#include "WutheringWave/GameData/DataTable/WWWeaponDataTable.h"
#include "WWWeaponStatWidget.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVE_API UWWWeaponStatWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateWindow(int32 CurrentID);

protected:
	void MakeDescriptionText(const FWWWeaponDevelopmentData* CurrentWeaponPtr, const FWWWeaponDataTable* DataRow);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> WeaponNameText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> LevelText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> WeaponTypeIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWWAsensionWidget> AscensionView;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWWStatWidget> MainStat1;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWWStatWidget> MainStat2;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> SkillNameText;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UMultiLineEditableTextBox> Description1;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UMultiLineEditableTextBox> Description2;
};
