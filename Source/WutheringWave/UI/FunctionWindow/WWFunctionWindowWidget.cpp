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

	auto GameInstance = GetGameInstance();
	if (!GameInstance) return;

	auto SubSystem = GameInstance->GetSubsystem<UWWSaveDataSubsystem>();

	if (SubSystem)
	{
		auto AccountSaveGame = SubSystem->GetAccountSaveGame();
		if (!AccountSaveGame) return;

		auto AcountInformation = AccountSaveGame->GetAccountInformation();

		if(AcountInformation)
		{
			if (NameTextBox)
				NameTextBox->SetText(FText::FromString(AcountInformation->Name));
			if (UIDTextBox)
				UIDTextBox->SetText(FText::Format(FTextFormat::FromString(TEXT("UID:{0}")), AcountInformation->UID));
			if (BirthDayTextBox)
				BirthDayTextBox->SetText(FText::Format(FTextFormat::FromString(TEXT("{0}월 {1}일")), AcountInformation->BirthDay.X, AcountInformation->BirthDay.Y));
			if (RankTextBox)
				RankTextBox->SetText(FText::Format(FTextFormat::FromString(TEXT("Rank.{0}")), AcountInformation->Rank));
			if (LevelTextBox)
				LevelTextBox->SetText(FText::Format(FTextFormat::FromString(TEXT("Lv:{0}")), AcountInformation->Level));
			if (ExpTextBox)
				ExpTextBox->SetText(FText::Format(FTextFormat::FromString(TEXT("{0}/{1}")), AcountInformation->Exp, 12800));
			if (UserWordTextBox)
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
