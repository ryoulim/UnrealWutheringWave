// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WWRoleStatWidget.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVE_API UWWRoleStatWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateWindow(int32 InRoleID);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UWWStatWidget> HpStatWindow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UWWStatWidget> AttackStatWindow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UWWStatWidget> DefenseStatWindow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UWWStatWidget> EnergyRegenStatWindow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UWWStatWidget> CritRateStatWindow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UWWStatWidget> CritDamageStatWindow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UImage> ElementIcon;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UTextBlock> CharacterNameText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UTextBlock> ElementTypeText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UWWAsensionWidget> RoleAscensionView;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UWWRoleDevLevelWidget> RoleDevLevelView;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 RoleID{};
};
