// Fill out your copyright notice in the Description page of Project Settings.


#include "WWRoleDevelopHeadWidget.h"
#include "WutheringWave/GameData/DataAsset/WWRoleDataAsset.h"
#include "Components/Image.h"

void UWWRoleDevelopHeadWidget::SetRoleImage(int32 InCharacterID)
{
    if (!RoleImage)
    {
        return;
    }

    if (auto DataAsset = UWWRoleDataAsset::Get(InCharacterID))
    {
        ButtonID = InCharacterID;
        RoleImage->SetBrushFromTexture(DataAsset->UITexture.Get(), true);
    }
}
