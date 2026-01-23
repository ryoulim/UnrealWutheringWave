
#include "WWCharacterDevelopmentData.h"

#include "WWWeaponDevelopmentData.h"
#include "GameData/DataTable/WWCharacterStatTable.h"
#include "SubSystem/WWDataTableIDSearchSubsystem.h"


bool UWWCharacterDevelopmentSaveGame::AddNewCharacter(int32 CharacterID, UWWWeaponDevelopmentSaveGame* WeaponSaveGame)
{
	if (CharacterMap.Find(CharacterID))
		return false;

	int32 Key = WeaponSaveGame->AddDefaultWeapon(GameInstance->GetSubsystem<UWWDataTableIDSearchSubsystem>()->
		GetRow<FWWCharacterStatTable>(CharacterID)->WeaponType, CharacterID);

	FWWCharacterDevelopmentData Data{};
	Data.EquipWeaponID = Key;
	CharacterMap.Add(CharacterID, Data);

	SaveData();

	return true;
}

int32 UWWCharacterDevelopmentSaveGame::GetSelectedCharatcterID() const
{
	if (PartyCharacter.IsValidIndex(CurrentPartyIndex))
	{
		return PartyCharacter[CurrentPartyIndex];
	}
	return 0;
}
