#include "WWRoleDevelopmentViewModel.h"
#include "Engine/AssetManager.h"
#include "TimerManager.h"

// Subsystems
#include "Subsystem/WWSaveDataSubsystem.h"
#include "SubSystem/WWDataTableIDSearchSubsystem.h"
#include "SubSystem/WWRoledevModelSubsystem.h"

// Data
#include "GameData/SaveGame/WWCharacterDevelopmentData.h"
#include "GameData/SaveGame/WWWeaponDevelopmentData.h"
#include "GameData/DataAsset/WWRoleDataAsset.h"
#include "GameData/DataAsset/WWWeaponDataAsset.h"
#include "GameData/DataTable/WWCharacterStatTable.h"

void UWWRoleDevelopmentViewModel::InitializeViewModel(UObject* InWorldContextObject)
{
	WorldContextObject = InWorldContextObject;
}

void UWWRoleDevelopmentViewModel::DeinitializeViewModel()
{
	if (!WorldContextObject) return;

	if (UGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance())
	{
		if (auto RoledevModelSubsystem = GameInstance->GetSubsystem<UWWRoledevModelSubsystem>())
		{
			RoledevModelSubsystem->ClosePreview();
		}
	}
}

void UWWRoleDevelopmentViewModel::LoadInitialData()
{
	if (!WorldContextObject) return;
	UGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance();
	if (!GameInstance) return;

	auto SaveSubsystem = GameInstance->GetSubsystem<UWWSaveDataSubsystem>();
	if (!SaveSubsystem || !SaveSubsystem->GetCharacterSaveGame() || !SaveSubsystem->GetWeaponSaveGame())
	{
		return;
	}

	CurrentRoleID = SaveSubsystem->GetCharacterSaveGame()->GetSelectedCharatcterID();

	TArray<FPrimaryAssetId> TargetIDs;
	for (auto& Character : SaveSubsystem->GetCharacterSaveGame()->CharacterMap)
	{
		TargetIDs.Add(UWWRoleDataAsset::GetID(Character.Key));
	}

	TSet<int32> WeaponIDs; 
	for (auto& Weapon : SaveSubsystem->GetWeaponSaveGame()->WeaponMap)
	{
		WeaponIDs.Add(Weapon.Value.WeaponID);
	}
	for (auto& ID : WeaponIDs)
	{
		TargetIDs.Add(UWWWeaponDataAsset::GetID(ID));
	}

	UAssetManager::Get().LoadPrimaryAssets(TargetIDs,
		{ TEXT("Mesh"), TEXT("UIAnimation"), TEXT("UITexture")},
		FStreamableDelegate::CreateUObject(this, &UWWRoleDevelopmentViewModel::OnMainLoadEnd));
}

void UWWRoleDevelopmentViewModel::OnMainLoadEnd()
{
	if (!WorldContextObject) return;

	// 프리뷰 열기
	if (UGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance())
	{
		if (auto RoledevModelSubsystem = GameInstance->GetSubsystem<UWWRoledevModelSubsystem>())
		{
			RoledevModelSubsystem->OpenPreview();
		}
	}

	UpdateDataAndBroadcast();
}

void UWWRoleDevelopmentViewModel::ChangeRole(int32 RoleID)
{
	CurrentRoleID = RoleID;

	UWWRoleDataAsset::Get(RoleID)->LoadPropsAssets(FSimpleDelegate::CreateLambda([this]()
	{
		UpdateDataAndBroadcast();
	}));
}

void UWWRoleDevelopmentViewModel::UpdateDataAndBroadcast()
{
	if (!WorldContextObject) return;

	UGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance();
	if (!GameInstance) return;

	auto SaveDataSubsystem = GameInstance->GetSubsystem<UWWSaveDataSubsystem>();
	auto DataTableIDSearchSubsystem = GameInstance->GetSubsystem<UWWDataTableIDSearchSubsystem>();
	auto RoledevModelSubsystem = GameInstance->GetSubsystem<UWWRoledevModelSubsystem>();

	if (!SaveDataSubsystem || !DataTableIDSearchSubsystem || !RoledevModelSubsystem) return;

	// 무기 정보 획득
	int32 SelectedWeaponID = 0;
	if (auto FoundRow = SaveDataSubsystem->GetCharacterSaveGame()->CharacterMap.Find(CurrentRoleID))
	{
		SelectedWeaponID = FoundRow->EquipWeaponID;
	}

	EWWWeaponTypeName SelectedWeaponType = EWWWeaponTypeName::Sword; // Default
	if (auto FoundRow = DataTableIDSearchSubsystem->GetRow<FWWCharacterStatTable>(CurrentRoleID))
	{
		SelectedWeaponType = FoundRow->WeaponType;
	}

	// 1. 상태 갱신 알림 (View에게 데이터 전달)
	OnRoleDataUpdated.Broadcast(CurrentRoleID, SelectedWeaponID, SelectedWeaponType);

	// 2. 모델 프리뷰 갱신
	RoledevModelSubsystem->SetPreviewRole(CurrentRoleID);

	// 틱 딜레이 후 애니메이션과 함께 프리뷰 다시 적용 (기존 로직 유지)
	WorldContextObject->GetWorld()->GetTimerManager().SetTimerForNextTick([RoledevModelSubsystem, RoleID = CurrentRoleID]()
	{
		if (RoledevModelSubsystem)
		{
			RoledevModelSubsystem->SetPreviewRole(RoleID);
		}
	});

	// 3. 렌더타겟 갱신 알림
	UTextureRenderTarget2D* RenderTarget = RoledevModelSubsystem->GetRenderTarget();
	OnPreviewUpdated.Broadcast(RenderTarget);
}
