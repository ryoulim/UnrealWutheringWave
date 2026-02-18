// Fill out your copyright notice in the Description page of Project Settings.


#include "WWLoadingLevelGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Role/WWRoleBase.h"

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
	// LoadingLevel에 머무는 클라이언트도 Pawn/카메라를 갖도록 (검은 화면 방지)
	DefaultPawnClass = AWWRoleBase::StaticClass();
}

void AWWLoadingLevelGameMode::BeginPlay()
{
	// 멀티플레이어: 로딩/세이브/레벨 이동은 서버에서만. 클라이언트는 대기 후 서버와 함께 MainLevel로 이동
	if (GetWorld() && GetWorld()->GetNetMode() == NM_Client)
	{
		return;
	}
	LoadGlobalAssets();
}

void AWWLoadingLevelGameMode::LoadGlobalAssets()
{
	/* ??로벌 ????????? ?????? 로드 */
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
	/* ????????? ???????????? 캐릭?????? 매쉬??? 기본 ??????메이??? 로드 */
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
	/* ???버에????? ????? ??????. ?????????????????? ???버??? ????????? ??? ????? ????????????? ???기서 OpenLevel ???출하?? ?????? */
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
