// Fill out your copyright notice in the Description page of Project Settings.

#include "WWFunctionWindowWidget.h"

#include "Components/EditableTextBox.h"
#include "Components/MultiLineEditableTextBox.h"
#include "WWFunctionSlideWindow.h"

#include "SubSystem/WWSaveDataSubsystem.h"
#include "GameData/SaveGame/WWAccountInformation.h"

void UWWFunctionWindowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto SubSystem = GetGameInstance()->GetSubsystem<UWWSaveDataSubsystem>();

	if (SubSystem)
	{
		auto AcountInformation = SubSystem->GetAccountSaveGame()->GetAccountInformation();

		if(AcountInformation)
		{
			NameTextBox->SetText(FText::FromString(AcountInformation->Name));
			UIDTextBox->SetText(FText::Format(FTextFormat::FromString(TEXT("UID:{0}")), AcountInformation->UID));
			BirthDayTextBox->SetText(FText::Format(FTextFormat::FromString(TEXT("{0}월 {1}일")), AcountInformation->BirthDay.X, AcountInformation->BirthDay.Y));
			RankTextBox->SetText(FText::Format(FTextFormat::FromString(TEXT("Rank.{0}")), AcountInformation->Rank));
			LevelTextBox->SetText(FText::Format(FTextFormat::FromString(TEXT("Lv:{0}")), AcountInformation->Level));
			ExpTextBox->SetText(FText::Format(FTextFormat::FromString(TEXT("{0}/{1}")), AcountInformation->Exp, 12800));
			UserWordTextBox->SetText(FText::FromString(AcountInformation->UserWord));
		}
	}
}

void UWWFunctionWindowWidget::Appear()
{
	ButtonSlideWidget->Appear();
}

void UWWFunctionWindowWidget::DisAppearButton()
{
	ButtonSlideWidget->Disappear();
}
