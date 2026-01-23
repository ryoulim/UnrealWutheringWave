// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Common/WWWindowBaseWidget.h"
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
	UFUNCTION()
	void OnMainLoadEnd();

	UFUNCTION(BlueprintCallable)
	void UpdateWindow();

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
};
