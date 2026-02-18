// Fill out your copyright notice in the Description page of Project Settings.

#include "WWSaveDataSubsystem.h"

#include "GameData/SaveGame/WWAccountInformation.h"
#include "GameData/SaveGame/WWCharacterDevelopmentData.h"
#include "GameData/SaveGame/WWEcoDevelopmentData.h"
#include "GameData/SaveGame/WWInventoryData.h"
#include "GameData/SaveGame/WWWeaponDevelopmentData.h"

void UWWSaveDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UWWSaveDataSubsystem::LoadAllData()
{
	if (bIsLoaded)
		return;

	bIsLoaded = true;

	auto GameInstance = GetGameInstance();
	/* LoadGame */
	AccountSaveGame = UWWSaveGameBase::LoadData<UWWAccountSaveGame>(TEXT("AccountData"), 0, GameInstance);
	CharacterSaveGame = UWWSaveGameBase::LoadData<UWWCharacterDevelopmentSaveGame>(TEXT("CharacterData"), 0, GameInstance);
	EcoSaveGame = UWWSaveGameBase::LoadData<UWWEcoDevelopmentSaveGame>(TEXT("EcoData"), 0, GameInstance);
	InventorySaveGame = UWWSaveGameBase::LoadData<UWWWWInventoryDataSaveGame>(TEXT("InventoryData"), 0, GameInstance);
	WeaponSaveGame = UWWSaveGameBase::LoadData<UWWWeaponDevelopmentSaveGame>(TEXT("WeaponData"), 0, GameInstance);

	/* 최초 생성 */
	if (CharacterSaveGame->CharacterMap.IsEmpty())
	{
		CharacterSaveGame->AddNewCharacter(5, WeaponSaveGame);
		CharacterSaveGame->AddNewCharacter(7, WeaponSaveGame);
		CharacterSaveGame->AddNewCharacter(32, WeaponSaveGame);

		CharacterSaveGame->AddNewCharacter(33, WeaponSaveGame);
		CharacterSaveGame->AddNewCharacter(34, WeaponSaveGame);
		CharacterSaveGame->AddNewCharacter(37, WeaponSaveGame);
		CharacterSaveGame->AddNewCharacter(40, WeaponSaveGame);
		CharacterSaveGame->AddNewCharacter(44, WeaponSaveGame);
		CharacterSaveGame->AddNewCharacter(45, WeaponSaveGame);
		CharacterSaveGame->AddNewCharacter(57, WeaponSaveGame);

		CharacterSaveGame->PartyCharacter = { 5, 7, 57 };
		CharacterSaveGame->CurrentPartyIndex = 0;
		CharacterSaveGame->SaveData();

		for (int i = 0; i < 30; ++i)
		{
			WeaponSaveGame->AddWeapon(21010056);
			WeaponSaveGame->AddWeapon(21010046);
			WeaponSaveGame->AddWeapon(21020056);
		}
	}
}
