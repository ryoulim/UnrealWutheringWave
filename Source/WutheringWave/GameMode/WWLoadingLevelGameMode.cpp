// Fill out your copyright notice in the Description page of Project Settings.


#include "WWLoadingLevelGameMode.h"
#include "Kismet/GameplayStatics.h"

#include "Headers/WWEnums.h"
#include "GameData/DataAsset/WWElementDataAsset.h"
#include "GameData/DataAsset/WWRoleBattleTypeDataAsset.h"
#include "GameData/DataAsset/WWRoleStatAsset.h"
#include "GameData/DataAsset/WWWeaponTypeDataAsset.h"
#include "GameData/DataAsset/WWRoleDataAsset.h"

#include "SubSystem/WWSaveDataSubsystem.h"
#include "GameData/SaveGame/WWCharacterDevelopmentData.h"

AWWLoadingLevelGameMode::AWWLoadingLevelGameMode()
{
}

void AWWLoadingLevelGameMode::BeginPlay()
{

	LoadGlobalAssets();
}

void AWWLoadingLevelGameMode::LoadGlobalAssets()
{
	/* 글로벌 데이터 에셋 로드 */
	UAssetManager::Get().StartInitialLoading();

	StreamableHandle = UAssetManager::Get().LoadPrimaryAssets({

		/* Element */
		UWWElementDataAsset::GetID(EWWElementName::Fire),
		UWWElementDataAsset::GetID(EWWElementName::Ice),
		UWWElementDataAsset::GetID(EWWElementName::Wind),
		UWWElementDataAsset::GetID(EWWElementName::Thunder),
		UWWElementDataAsset::GetID(EWWElementName::Light),
		UWWElementDataAsset::GetID(EWWElementName::Dark),

		/* RoleStat */
		UWWRoleStatAsset::GetID(EWWStatName::HP),
		UWWRoleStatAsset::GetID(EWWStatName::Attack),
		UWWRoleStatAsset::GetID(EWWStatName::Defense),
		UWWRoleStatAsset::GetID(EWWStatName::EnergyRegen),
		UWWRoleStatAsset::GetID(EWWStatName::CritRate),
		UWWRoleStatAsset::GetID(EWWStatName::CritDamage),

		/* WeaponType */
		UWWWeaponTypeDataAsset::GetID(EWWWeaponTypeName::Sword),
		UWWWeaponTypeDataAsset::GetID(EWWWeaponTypeName::Broadblade),
		UWWWeaponTypeDataAsset::GetID(EWWWeaponTypeName::Pistols),
		UWWWeaponTypeDataAsset::GetID(EWWWeaponTypeName::Rectifier),
		UWWWeaponTypeDataAsset::GetID(EWWWeaponTypeName::Gauntlets),
		},
		{ TEXT("Default") },
		FStreamableDelegate::CreateUObject(this, &AWWLoadingLevelGameMode::LoadPartyCharacter)
		);
}

void AWWLoadingLevelGameMode::LoadPartyCharacter()
{
	/* 파티에 들어있는 캐릭터들 매쉬와 기본 애니메이션 로드 */
	auto SaveDataSubsystem = GetGameInstance()->GetSubsystem<UWWSaveDataSubsystem>();
	SaveDataSubsystem->LoadAllData();

	TArray<FPrimaryAssetId> AsetIDs;
	for (auto CharacterID : SaveDataSubsystem->GetCharacterSaveGame()->PartyCharacter)
	{
		AsetIDs.Add(UWWRoleDataAsset::GetID(CharacterID));
	}

	StreamableHandle = UAssetManager::Get().LoadPrimaryAssets(
		AsetIDs,
		{ TEXT("Mesh"), TEXT("Material") },
		FStreamableDelegate::CreateUObject(this, &AWWLoadingLevelGameMode::OnLoadEnd)
		);
}

void AWWLoadingLevelGameMode::OnLoadEnd()
{
	/* 서버에서만 레벨 이동. 클라이언트는 서버가 이동할 때 함께 이동하므로 여기서 OpenLevel 호출하지 않음 */
	if (GetWorld() && GetWorld()->GetNetMode() != NM_Client)
	{
		UGameplayStatics::OpenLevel(
			this,
			FName("MainLevel"),
			true,
			TEXT("Listen")
		);
	}
}
