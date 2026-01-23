// Fill out your copyright notice in the Description page of Project Settings.


#include "WWWeaponStatWidget.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "UI/RoleDevelopmentWindow/Common/WWStatWidget.h"
#include "UI/RoleDevelopmentWindow/Common/WWAsensionWidget.h"

#include "GameData/SaveGame/WWCharacterDevelopmentData.h"
#include "GameData/DataAsset/WWWeaponTypeDataAsset.h"

#include "SubSystem/WWDataTableIDSearchSubsystem.h"
#include "SubSystem/WWSaveDataSubsystem.h"


void UWWWeaponStatWidget::UpdateWindow(int32 CurrentID)
{
	auto SaveDataSubSystem = GetGameInstance()->GetSubsystem<UWWSaveDataSubsystem>();
	if (!SaveDataSubSystem)
		return;

	const FWWWeaponDevelopmentData* CurrentWeaponPtr = SaveDataSubSystem->GetWeaponSaveGame()->WeaponMap.Find(CurrentID);
	if (!CurrentWeaponPtr)
		return;

	auto DataTableSubSystem = GetGameInstance()->GetSubsystem<UWWDataTableIDSearchSubsystem>();
	if (!DataTableSubSystem)
		return;

	const FWWWeaponDataTable* DataRow = DataTableSubSystem->GetRow<FWWWeaponDataTable>(CurrentWeaponPtr->WeaponID);
	if (!DataRow)
		return;

	auto TypeData = UWWWeaponTypeDataAsset::Get(DataRow->Type);
	if (!TypeData)
		return;

	LevelText->SetText(
		FText::Format(FTextFormat::FromString(TEXT("Lv. {CurrentLevel}/{MaxLevel}"))
			, CurrentWeaponPtr->Level, 10 + (CurrentWeaponPtr->Ascension * 10)));

	WeaponNameText->SetText(FText::FromName(DataRow->Name_Ko));

	WeaponTypeIcon->SetBrushFromTexture(TypeData->DefaultIcon.Get());

	AscensionView->UpdateWindow(CurrentWeaponPtr->Ascension);

	MainStat1->UpdateView(DataRow->StatType1, 
		MainStat1->CalcValue(CurrentWeaponPtr->Level, DataRow->BaseStat1, DataRow->GrowthStat1), true);
	MainStat2->UpdateView(DataRow->StatType2,
		MainStat1->CalcValue(CurrentWeaponPtr->Level, DataRow->BaseStat2, DataRow->GrowthStat2), true);

	SkillNameText->SetText(FText::FromString(DataRow->SkillName));

	MakeDescriptionText(CurrentWeaponPtr, DataRow);
	Description2->SetText(FText::FromString(DataRow->Description2));
}

void UWWWeaponStatWidget::MakeDescriptionText(const FWWWeaponDevelopmentData* CurrentWeaponPtr, const FWWWeaponDataTable* DataRow)
{
	if (!Description1)
		return;

	TArray<FFormatArgumentValue> Args;
	for (const FAscensionAbility& Ability : DataRow->AscensionAbility)
	{
		switch (CurrentWeaponPtr->ResonanceChain)
		{
		case 0:
			Args.Add(Ability.AscensionGrowthStat1);
			break;
		case 1:
			Args.Add(Ability.AscensionGrowthStat2);
			break;
		case 2:
			Args.Add(Ability.AscensionGrowthStat3);
			break;
		case 3:
			Args.Add(Ability.AscensionGrowthStat4);
			break;
		case 4:
			Args.Add(Ability.AscensionGrowthStat5);
			break;
		default :
			break;
		}
	}

	Description1->SetText(FText::Format(FTextFormat::FromString(DataRow->Description1), Args));
}
