
#include "WWWeaponDevelopmentData.h"
#include "Engine/AssetManager.h"
#include "WutheringWave/GameData/DataAsset/WWWeaponTypeDataAsset.h"

void UWWWeaponDevelopmentSaveGame::AddWeapon(int32 WeaponID)
{
	int32 Key = FindEmptySlot();

	FWWWeaponDevelopmentData Data{};
	Data.WeaponID = WeaponID;

	WeaponMap.Add(Key, Data);

	SaveData();
}

int32 UWWWeaponDevelopmentSaveGame::AddDefaultWeapon(EWWWeaponTypeName WeaponType, int32 EquipCharacterID)
{
	int32 Key = FindEmptySlot();

	auto DataAsset = UWWWeaponTypeDataAsset::Get(WeaponType);
	
	if (!DataAsset)
		return -1;

	FWWWeaponDevelopmentData Data{};
	Data.WeaponID = DataAsset->DefaultWeaponID;
	Data.EquipCharacterID = EquipCharacterID;

	WeaponMap.Add(Key, Data);
	SaveData();

	return Key;
}

int32 UWWWeaponDevelopmentSaveGame::FindEmptySlot()
{
	int32 Num = WeaponMap.Num();

	for (int32 i = Num; i > 0; --i)
	{
		if (!WeaponMap.Contains(i))
			return i;
	}
	return Num;
}