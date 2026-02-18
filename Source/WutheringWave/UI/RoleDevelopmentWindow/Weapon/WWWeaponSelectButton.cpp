// Fill out your copyright notice in the Description page of Project Settings.

#include "WWWeaponSelectButton.h"
#include "Components/Image.h"

#include "SubSystem/WWDataTableIDSearchSubsystem.h"
#include "GameData/DataTable/WWWeaponDataTable.h"
#include "GameData/DataAsset/WWWeaponDataAsset.h"

void UWWWeaponSelectButton::SetImage(int32 InWeaponID)
{
    if (!WeaponImage)
    {
        return;
    }

    if (const UWWWeaponDataAsset* WeaponData = UWWWeaponDataAsset::Get(InWeaponID))
    {
        ButtonID = InWeaponID;
        WeaponImage->SetBrushFromTexture(WeaponData->UITexture.Get(), true);
    }
    if (const FWWWeaponDataTable* WeaponDataTable = GetGameInstance()->GetSubsystem<UWWDataTableIDSearchSubsystem>()->GetRow<FWWWeaponDataTable>(InWeaponID))
    {
        WeaponType = WeaponDataTable->Type;
    }
}