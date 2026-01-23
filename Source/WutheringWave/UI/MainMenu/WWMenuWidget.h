// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Common/WWWindowBaseWidget.h"
#include "WWMenuWidget.generated.h"

USTRUCT()
struct FUIWindowEntry
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<class UWWWindowBaseWidget> Widget;

	float LastActiveTime = { 0.f };
	bool bActive = { false };
};

/**
 * 
 */
UCLASS()
class WUTHERINGWAVE_API UWWMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry,float InDeltaTime) override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	/* WindowType */
protected:
	UPROPERTY(EditDefaultsOnly, Category = DefaltSetting)
	TMap<int32, TSubclassOf<class UWWWindowBaseWidget>> WindowTypes;

	UPROPERTY(EditDefaultsOnly, Category = DefaltSetting)
	float InactiveDestroyTime;

	UPROPERTY(EditDefaultsOnly, Category = DefaltSetting)
	float FadeAnimationSpeed;

	/* Default Widget */
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UImage> FadeImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UWWFunctionWindowWidget> FunctionWindow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> RootCanvas;

	/* Animation */
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetAnim), Transient)
	TObjectPtr<class UWidgetAnimation> FadeInAnim;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetAnim), Transient)
	TObjectPtr<class UWidgetAnimation> FadeOutAnim;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetAnim), Transient)
	TObjectPtr<class UWidgetAnimation> OpenMenuAnim;

	UFUNCTION()
	void OnFadeInAnimEnd();

	UFUNCTION()
	void OnFadeOutAnimEnd();

	UFUNCTION()
	void OnOpenMenuAnimEnd();

	/* Open And Close */
public:
	UFUNCTION(BlueprintCallable)
	void OpenMenu();

	UFUNCTION(BlueprintCallable)
	void CloseMenu();

	/* Change Window */
public:
	UFUNCTION(BlueprintCallable)
	void ChangeWindow(int32 InTargetWindow);

	UFUNCTION()
	void ChangeWindowToFunction();
	
	UFUNCTION()
	void SetWindowLoadEnd();

protected :
	TMap<int32, FUIWindowEntry> WindowMap;
	void ShowWindow(int32 WindowType);
	void HideWindow(int32 WindowType);

	int32 CurretnWindowID;
	int32 TargetWindowID;
	bool bIsWindowLoadEnd;
	bool bFadeOutAnimEnd;
};
