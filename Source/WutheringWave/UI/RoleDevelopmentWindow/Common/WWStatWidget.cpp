// Fill out your copyright notice in the Description page of Project Settings.


#include "WWStatWidget.h"
#include "Components/Image.h"
#include "Components/EditableTextBox.h"

#include "WutheringWave/GameData/DataAsset/WWRoleStatAsset.h"

void UWWStatWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (auto DataAsset = UWWRoleStatAsset::Get(StatType))
	{
		/* 아이콘 변경*/
		StatIcon->SetBrushFromTexture(DataAsset->Icon.Get(), true);

		/* 이름 변경 */
		StatNameText->SetText(FText::FromString(DataAsset->Name_Ko));
	}

	/* 스텟 값 변경 */
	if (bIsPercent)
	{
		StatValue = FMath::TruncToFloat(StatValue * 10) / 10;
		StatValueText->SetText(FText::Format(FTextFormat::FromString(TEXT("{0}%")), StatValue));
	}
	else
	{
		StatValueText->SetText(FText::AsNumber(static_cast<int32>(StatValue)));
	}

	/* BG 활성화 */
	if (bActiveBG)
	{
		BackGround->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		BackGround->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UWWStatWidget::UpdateView(EWWStatName StatName, float Value, bool isPercent)
{
	StatType = StatName;
	StatValue = Value;
	bIsPercent = isPercent;

	if (auto DataAsset = UWWRoleStatAsset::Get(StatType))
	{
		/* 아이콘 변경*/
		StatIcon->SetBrushFromTexture(DataAsset->Icon.Get(), true);

		/* 이름 변경 */
		StatNameText->SetText(FText::FromString(DataAsset->Name_Ko));
	}

	/* 스텟 값 변경 */
	if (bIsPercent)
	{
		StatValue = FMath::TruncToFloat(StatValue * 10) / 10;
		StatValueText->SetText(FText::Format(FTextFormat::FromString(TEXT("{0}%")), StatValue));
	}
	else
	{
		StatValueText->SetText(FText::AsNumber(static_cast<int32>(StatValue)));
	}

	/* BG 활성화 */
	if (bActiveBG)
	{
		BackGround->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		BackGround->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UWWStatWidget::UpdateValue(int32 Level, float BaseValue, float ValuePerLv)
{
	StatValue = CalcValue(Level, BaseValue, ValuePerLv);

	/* 스텟 값 변경 */
	if (bIsPercent)
	{
		StatValue = FMath::TruncToFloat(StatValue * 10) / 10;
		StatValueText->SetText(FText::Format(FTextFormat::FromString(TEXT("{0}%")), StatValue));
	}
	else
	{
		StatValueText->SetText(FText::AsNumber(static_cast<int32>(StatValue)));
	}
}

float UWWStatWidget::CalcValue(int32 Level, float BaseValue, float ValuePerLv)
{
	return BaseValue + (Level - 1) * ValuePerLv;
}
