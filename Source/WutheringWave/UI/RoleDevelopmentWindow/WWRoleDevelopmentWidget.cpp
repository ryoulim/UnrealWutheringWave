// Fill out your copyright notice in the Description page of Project Settings.


#include "WWRoleDevelopmentWidget.h"
#include "Engine/AssetManager.h"

#include "Components/Image.h"
#include "Engine/TextureRenderTarget2D.h"

#include "Subsystem/WWSaveDataSubsystem.h"
#include "SubSystem/WWDataTableIDSearchSubsystem.h"
#include "SubSystem/WWRoledevModelSubsystem.h"

#include "GameData/SaveGame/WWCharacterDevelopmentData.h"
#include "GameData/SaveGame/WWWeaponDevelopmentData.h"
#include "GameData/DataAsset/WWRoleDataAsset.h"
#include "GameData/DataAsset/WWWeaponDataAsset.h"
#include "GameData/DataTable/WWCharacterStatTable.h"

#include "SelectRole/WWRoleSlideWidget.h"
#include "Role/WWRoleStatWidget.h"
#include "Weapon/WWWeaponStatWidget.h"
#include "Weapon/WWWeaponSelectWidget.h"

void UWWRoleDevelopmentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	/* 지금 세이브 데이터에 있는 놈들만 로드 */
	auto SubSystem = GetGameInstance()->GetSubsystem<UWWSaveDataSubsystem>();
	if (!SubSystem)
		return;

	auto RoleSaveGame = SubSystem->GetCharacterSaveGame();
	if (!RoleSaveGame)
		return;

	auto WeaponSaveGame = SubSystem->GetWeaponSaveGame();
	if (!WeaponSaveGame)
		return;

	/* 캐릭터 로드 */
	TArray<FPrimaryAssetId> TargetIDs;
	for (auto& Character : RoleSaveGame->CharacterMap)
	{
		TargetIDs.Add(UWWRoleDataAsset::GetID(Character.Key));
	}

	/* 무기 로드 */
	TSet<int32> WeaponIDs; // 무기 중복 방지용
	for (auto& Weapon : WeaponSaveGame->WeaponMap)
	{
		WeaponIDs.Add(Weapon.Value.WeaponID);
	}
	for (auto& ID : WeaponIDs)
	{
		TargetIDs.Add(UWWWeaponDataAsset::GetID(ID));
	}

	auto StreamableHandle = UAssetManager::Get().LoadPrimaryAssets(TargetIDs,
		{ TEXT("Mesh"), TEXT("UIAnimation"), TEXT("UITexture")},
		FStreamableDelegate::CreateUObject(this, &UWWRoleDevelopmentWidget::OnMainLoadEnd));
}

void UWWRoleDevelopmentWidget::NativeDestruct()
{
	Super::NativeDestruct();
	if (auto RoledevModelSubsystem = GetGameInstance()->GetSubsystem<UWWRoledevModelSubsystem>())
	{
		RoledevModelSubsystem->ClosePreview();
	}
}

void UWWRoleDevelopmentWidget::OnMainLoadEnd()
{
	UpdateWindow();
	OnWWWindowBaseLoadEnd.Broadcast();
}

void UWWRoleDevelopmentWidget::UpdateWindow()
{
	/* 로딩 끝나고 처음 불리는 함수임 */

	auto SaveDataSubsystem = GetGameInstance()->GetSubsystem<UWWSaveDataSubsystem>();
	if (!SaveDataSubsystem)
		return;

	auto DataTableIDSearchSubsystem = GetGameInstance()->GetSubsystem<UWWDataTableIDSearchSubsystem>();
	if (!DataTableIDSearchSubsystem)
		return;

	auto RoledevModelSubsystem = GetGameInstance()->GetSubsystem<UWWRoledevModelSubsystem>();
	if (!RoledevModelSubsystem)
		return;

	/* 스텟 업데이트 */
	int32 SelectedCharacterID = SaveDataSubsystem->GetCharacterSaveGame()->GetSelectedCharatcterID();
	RoleStatWidget->UpdateWindow(SelectedCharacterID);

	/* 무기 업데이트*/
	if (auto FoundRow = SaveDataSubsystem->GetCharacterSaveGame()->CharacterMap.Find(SelectedCharacterID))
	{
		int32 SelectedWeaponID = FoundRow->EquipWeaponID;
		WeaponStatWidget->UpdateWindow(SelectedWeaponID);
	}

	/* 무기 종류 업데이트 */
	if (auto FoundRow = DataTableIDSearchSubsystem->GetRow<FWWCharacterStatTable>(SelectedCharacterID))
	{
		EWWWeaponTypeName SelectedWeaponType = FoundRow->WeaponType;
		WeaponSelectWidget->UpdateWindowbyType(SelectedWeaponType);
	}

	/* 버튼 재구성 */
	RoleSlideWidget->SetButtonImage();

	/* 프리뷰 셋팅 */
	RoledevModelSubsystem->OpenPreview();
	if (auto SaveDataSubSystem = GetGameInstance()->GetSubsystem<UWWSaveDataSubsystem>())
	{
		int32 RoleId = SaveDataSubSystem->GetCharacterSaveGame()->GetSelectedCharatcterID();
		RoledevModelSubsystem->SetPreviewRole(RoleId);

		// AnimInstance가 준비될 때까지 약간의 시간이 필요할 수 있으므로
		// 다음 프레임에 애니메이션을 재시작하도록 함
		GetWorld()->GetTimerManager().SetTimerForNextTick([this, RoledevModelSubsystem, RoleId]()
		{
			if (RoledevModelSubsystem)
			{
				// 애니메이션을 확실히 재시작
				RoledevModelSubsystem->SetPreviewRole(RoleId);
			}
		});

		// RenderTarget이 유효한지 확인
		UTextureRenderTarget2D* RenderTarget = RoledevModelSubsystem->GetRenderTarget();
		if (RenderTarget && CharacterPreview)
		{
			UMaterialInstanceDynamic* MID = CharacterPreview->GetDynamicMaterial();
			if (MID)
			{
				MID->SetTextureParameterValue(TEXT("Texture"), RenderTarget);
			}
		}
	}
}

void UWWRoleDevelopmentWidget::OnRoleButtonClicked(int32 ButtonID)
{
	/* 캐릭터 바꾸는 버튼 눌렀을 때 */

	/* 로드먼저 하고... 로드 끝나면 람다식에서 업데이트 */
	UWWRoleDataAsset::Get(ButtonID)->LoadPropsAssets(FSimpleDelegate::CreateLambda([this, ButtonID]()
	{
		auto SaveDataSubsystem = GetGameInstance()->GetSubsystem<UWWSaveDataSubsystem>();
		if (!SaveDataSubsystem)
			return;

		auto DataTableIDSearchSubsystem = GetGameInstance()->GetSubsystem<UWWDataTableIDSearchSubsystem>();
		if (!DataTableIDSearchSubsystem)
			return;

		auto RoledevModelSubsystem = GetGameInstance()->GetSubsystem<UWWRoledevModelSubsystem>();
		if (!RoledevModelSubsystem)
			return;

		/* 스텟 업데이트 */
		RoleStatWidget->UpdateWindow(ButtonID);

		/* 무기 업데이트*/
		if (auto FoundRow = SaveDataSubsystem->GetCharacterSaveGame()->CharacterMap.Find(ButtonID))
		{
			int32 SelectedWeaponID = FoundRow->EquipWeaponID;
			WeaponStatWidget->UpdateWindow(SelectedWeaponID);
		}

		/* 무기 종류 업데이트 */
		if (auto FoundRow = DataTableIDSearchSubsystem->GetRow<FWWCharacterStatTable>(ButtonID))
		{
			EWWWeaponTypeName SelectedWeaponType = FoundRow->WeaponType;
			WeaponSelectWidget->UpdateWindowbyType(SelectedWeaponType);
		}

		/* 프리뷰 업데이트 */
		RoledevModelSubsystem->SetPreviewRole(ButtonID);

		// RenderTarget 업데이트
		UTextureRenderTarget2D* RenderTarget = RoledevModelSubsystem->GetRenderTarget();
		if (RenderTarget && CharacterPreview)
		{
			UMaterialInstanceDynamic* MID = CharacterPreview->GetDynamicMaterial();
			if (MID)
			{
				MID->SetTextureParameterValue(TEXT("Texture"), RenderTarget);
			}
		}
	}));
}
