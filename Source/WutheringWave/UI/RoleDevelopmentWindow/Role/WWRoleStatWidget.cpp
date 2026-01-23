// Fill out your copyright notice in the Description page of Project Settings.


#include "WWRoleStatWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "UI/RoleDevelopmentWindow/Common/WWAsensionWidget.h"
#include "UI/RoleDevelopmentWindow/Common/WWRoleDevLevelWidget.h"
#include "UI/RoleDevelopmentWindow/Common/WWStatWidget.h"

#include "SubSystem/WWDataTableIDSearchSubsystem.h"
#include "GameData/DataTable/WWCharacterStatTable.h"
#include "GameData/DataAsset/WWElementDataAsset.h"

#include "Subsystem/WWSaveDataSubsystem.h"
#include "GameData/SaveGame/WWCharacterDevelopmentData.h"

void UWWRoleStatWidget::UpdateWindow(int32 InRoleID)
{
	RoleID = InRoleID;
	auto DataRow = GetGameInstance()->GetSubsystem<UWWDataTableIDSearchSubsystem>()->GetRow<FWWCharacterStatTable>(InRoleID);
	if (!DataRow)
		return;

	auto ElementData = UWWElementDataAsset::Get(DataRow->ElementType);
	if (!ElementData)
		return;

	auto SubSystem = GetGameInstance()->GetSubsystem<UWWSaveDataSubsystem>();
	if (!SubSystem)
		return;

	auto CharacterDevData = SubSystem->GetCharacterSaveGame()->CharacterMap.Find(InRoleID);
	if (!CharacterDevData)
		return;

	ElementIcon->SetBrushFromTexture(ElementData->RoundIcon.Get(), true);
	CharacterNameText->SetText(FText::FromString(DataRow->CharacterName_Ko));
	ElementTypeText->SetText(FText::FromString(ElementData->Name_Ko));

	HpStatWindow->UpdateValue(CharacterDevData->Level, DataRow->MaxHp, DataRow->MaxHpPerLV);
	AttackStatWindow->UpdateValue(CharacterDevData->Level, DataRow->Attack, DataRow->AttackPerLV);
	DefenseStatWindow->UpdateValue(CharacterDevData->Level, DataRow->Defense, DataRow->DefensePerLV);
	EnergyRegenStatWindow->UpdateValue(CharacterDevData->Level, DataRow->EnergyRegen, DataRow->MaxHpPerLV);
	CritRateStatWindow->UpdateValue(CharacterDevData->Level, DataRow->CritRate, DataRow->CritDamagePerLV);
	CritDamageStatWindow->UpdateValue(CharacterDevData->Level, DataRow->CritDamage, DataRow->CritDamagePerLV);

	RoleAscensionView->UpdateWindow(CharacterDevData->Ascension);
	RoleDevLevelView->UpdateWindow(CharacterDevData->Level, CharacterDevData->Ascension * 10 + 20);
}
