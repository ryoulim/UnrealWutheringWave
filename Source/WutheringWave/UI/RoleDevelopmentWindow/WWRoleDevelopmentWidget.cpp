// Fill out your copyright notice in the Description page of Project Settings.


#include "WWRoleDevelopmentWidget.h"
#include "WWRoleDevelopmentViewModel.h"

#include "Components/Image.h"
#include "Engine/TextureRenderTarget2D.h"

#include "SelectRole/WWRoleSlideWidget.h"
#include "Role/WWRoleStatWidget.h"
#include "Weapon/WWWeaponStatWidget.h"
#include "Weapon/WWWeaponSelectWidget.h"

void UWWRoleDevelopmentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 1. ViewModel 생성 및 초기화
	ViewModel = NewObject<UWWRoleDevelopmentViewModel>(this);
	ViewModel->InitializeViewModel(this);

	// 2. 이벤트 바인딩 (수동적 View: Model의 상태 변화를 통보받음)
	ViewModel->OnRoleDataUpdated.AddDynamic(this, &UWWRoleDevelopmentWidget::OnRoleDataUpdated);
	ViewModel->OnPreviewUpdated.AddDynamic(this, &UWWRoleDevelopmentWidget::OnPreviewUpdated);

	// 3. 비즈니스 로직(데이터 로드) 실행 위임
	ViewModel->LoadInitialData();
}

void UWWRoleDevelopmentWidget::NativeDestruct()
{
	Super::NativeDestruct();
	
	if (ViewModel)
	{
		ViewModel->DeinitializeViewModel();
	}
}

void UWWRoleDevelopmentWidget::OnRoleDataUpdated(int32 RoleID, int32 WeaponID, EWWWeaponTypeName WeaponType)
{
	// 상태 업데이트 델리게이트가 호출되면 UI 갱신만 수행
	RoleStatWidget->UpdateWindow(RoleID);
	WeaponStatWidget->UpdateWindow(WeaponID);
	WeaponSelectWidget->UpdateWindowbyType(WeaponType);
	RoleSlideWidget->SetButtonImage();
	
	// 최초 로드 완료 알림
	static bool bIsFirstLoad = true;
	if (bIsFirstLoad)
	{
		OnWWWindowBaseLoadEnd.Broadcast();
		bIsFirstLoad = false;
	}
}

void UWWRoleDevelopmentWidget::OnPreviewUpdated(UTextureRenderTarget2D* RenderTarget)
{
	// 렌더타겟 갱신 델리게이트가 호출되면 재질만 교체
	if (RenderTarget && CharacterPreview)
	{
		UMaterialInstanceDynamic* MID = CharacterPreview->GetDynamicMaterial();
		if (MID)
		{
			MID->SetTextureParameterValue(TEXT("Texture"), RenderTarget);
		}
	}
}

void UWWRoleDevelopmentWidget::OnRoleButtonClicked(int32 ButtonID)
{
	if (ViewModel)
	{
		// 사용자의 조작(View 입력)을 ViewModel(조작자)에게 전달
		ViewModel->ChangeRole(ButtonID);
	}
}
