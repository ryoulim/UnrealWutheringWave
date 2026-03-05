// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Common/WWWindowBaseWidget.h"
#include "GameData/DataTable/WWCharacterStatTable.h"
#include "WWRoleDevelopmentWidget.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVE_API UWWRoleDevelopmentWidget : public UWWWindowBaseWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	// ViewModel에서 전달받는 상태 업데이트 이벤트
	UFUNCTION()
	void OnRoleDataUpdated(int32 RoleID, int32 WeaponID, EWWWeaponTypeName WeaponType);

	// ViewModel에서 전달받는 렌더링(프리뷰) 업데이트 이벤트
	UFUNCTION()
	void OnPreviewUpdated(class UTextureRenderTarget2D* RenderTarget);

	UFUNCTION(BlueprintCallable)
	void OnRoleButtonClicked(int32 ButtonID);

	/* BindWidget */
protected:
	/* 캐릭터 미리보기 */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UImage> CharacterPreview;

	/* 캐릭터 관련 */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UWWRoleSlideWidget> RoleSlideWidget;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UWWRoleStatWidget> RoleStatWidget;

	/* 무기 관련*/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UWWWeaponStatWidget> WeaponStatWidget;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UWWWeaponSelectWidget> WeaponSelectWidget;

protected:
	// ViewModel 인스턴스 (View는 자신의 상태를 관리할 ViewModel를 가집니다)
	UPROPERTY(BlueprintReadOnly, Category = "ViewModel")
	TObjectPtr<class UWWRoleDevelopmentViewModel> ViewModel;
};
