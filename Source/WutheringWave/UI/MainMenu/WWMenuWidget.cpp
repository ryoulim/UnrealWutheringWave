// Fill out your copyright notice in the Description page of Project Settings.


#include "WWMenuWidget.h"

#include "WutheringWave/Interface/WWMenuInterface.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"

#include "Animation/WidgetAnimation.h"
#include "../Common/WWWindowBaseWidget.h"
#include "../FunctionWindow/WWFunctionWindowWidget.h"

void UWWMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    FWidgetAnimationDynamicEvent OnFadeInEndEvent;
    OnFadeInEndEvent.BindUFunction(this, TEXT("OnFadeInAnimEnd"));
    BindToAnimationFinished(FadeInAnim, OnFadeInEndEvent);

    FWidgetAnimationDynamicEvent OnFadeOutEndEvent;
    OnFadeOutEndEvent.BindUFunction(this, TEXT("OnFadeOutAnimEnd"));
    BindToAnimationFinished(FadeOutAnim, OnFadeOutEndEvent);

    FWidgetAnimationDynamicEvent OnOpenMenuEndEvent;
    OnOpenMenuEndEvent.BindUFunction(this, TEXT("OnOpenMenuAnimEnd"));
    BindToAnimationFinished(OpenMenuAnim, OnOpenMenuEndEvent);

    FunctionWindow->OnWWWindowBaseCloseCall.AddDynamic(this, &UWWMenuWidget::CloseMenu);
}

void UWWMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    SetIsFocusable(true);

    UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(FadeImage->Slot);
    if (PanelSlot)
    {
        PanelSlot->SetZOrder(10);
    }
}

void UWWMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    const float Now = GetWorld()->GetTimeSeconds();

    for (auto It = WindowMap.CreateIterator(); It; ++It)
    {
        FUIWindowEntry& Entry = It.Value();

        if (!Entry.bActive && Entry.Widget)
        {
            if (Now - Entry.LastActiveTime > InactiveDestroyTime)
            {
                Entry.Widget->RemoveFromParent();
                Entry.Widget = nullptr;

                It.RemoveCurrent();
            }
        }
    }
}

FReply UWWMenuWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    if (InKeyEvent.GetKey() == EKeys::Tab)
    {
        CloseMenu();
    }

    return FReply::Handled();
}

void UWWMenuWidget::OnFadeInAnimEnd()
{
    FadeImage->SetVisibility(ESlateVisibility::Collapsed);
}

void UWWMenuWidget::OnFadeOutAnimEnd()
{
    HideWindow(CurretnWindowID);
    ShowWindow(TargetWindowID);
    CurretnWindowID = TargetWindowID;
    bFadeOutAnimEnd = true;

    if (bIsWindowLoadEnd)
    {
        PlayAnimation(FadeInAnim, 0.f, 1, EUMGSequencePlayMode::Forward, FadeAnimationSpeed);
    }
}

void UWWMenuWidget::OnOpenMenuAnimEnd()
{
    FunctionWindow->Appear();
}

void UWWMenuWidget::OpenMenu()
{
    SetVisibility(ESlateVisibility::Visible);
    PlayAnimation(OpenMenuAnim);
    SetKeyboardFocus();
}

void UWWMenuWidget::CloseMenu()
{
    if (IWWMenuInterface* PlayerController = Cast<IWWMenuInterface>(GetOwningPlayer()))
    {
        PlayerController->CloseMenu();
    }

    SetVisibility(ESlateVisibility::Hidden);
    FunctionWindow->DisAppearButton();
}

void UWWMenuWidget::ChangeWindow(int32 InTargetWindow)
{
    bIsWindowLoadEnd = true;
    bFadeOutAnimEnd = false;

    if (0 != InTargetWindow)
    {
        //윈도우 생성하고 로드하는 로직 여기로 옮기는게 좋을듯?
        FUIWindowEntry& Entry = WindowMap.FindOrAdd(InTargetWindow);

        if (!Entry.Widget)
        {
            auto Type = WindowTypes.Find(InTargetWindow);
            if (!Type)
            {
                WindowMap.Remove(InTargetWindow);
                return;
            }

            APlayerController* PC = GetWorld()->GetFirstPlayerController();
            Entry.Widget = CreateWidget<UWWWindowBaseWidget>(PC, *Type);
            Entry.Widget->OnWWWindowBaseLoadEnd.AddDynamic(this, &UWWMenuWidget::SetWindowLoadEnd);

            Entry.Widget->SetVisibility(ESlateVisibility::Hidden);
            bIsWindowLoadEnd = false;
            RootCanvas->AddChild(Entry.Widget);

            if (Entry.Widget)
            {
                Entry.Widget->OnWWWindowBaseCloseCall.AddDynamic(this, &UWWMenuWidget::ChangeWindowToFunction);
                Entry.Widget->SetIsFocusable(true);

                UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(Entry.Widget->Slot);
                if (PanelSlot)
                {
                    PanelSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
                    PanelSlot->SetOffsets(FMargin(0.f, 0.f, 0.f, 0.f));
                }
            }
        }
    }

    TargetWindowID = InTargetWindow;
    PlayAnimation(FadeOutAnim, 0.f, 1, EUMGSequencePlayMode::Forward, FadeAnimationSpeed);
}

void UWWMenuWidget::ChangeWindowToFunction()
{
    ChangeWindow(0);
}

void UWWMenuWidget::SetWindowLoadEnd()
{
    bIsWindowLoadEnd = true;
    if (bFadeOutAnimEnd)
    {
        PlayAnimation(FadeInAnim, 0.f, 1, EUMGSequencePlayMode::Forward, FadeAnimationSpeed);
    }
}

void UWWMenuWidget::ShowWindow(int32 WindowType)
{
    if (0 == WindowType)
    {
        FunctionWindow->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
        return;
    }

    FUIWindowEntry* Entry = WindowMap.Find(WindowType);
    if (!Entry || !Entry->Widget)
    {
        return;
    }

    Entry->Widget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
    Entry->Widget->SetKeyboardFocus();
    Entry->bActive = true;
}
    
void UWWMenuWidget::HideWindow(int32 WindowType)
{
    if (0 == WindowType)
    {
        FunctionWindow->SetVisibility(ESlateVisibility::Collapsed);
        return;
    }

    if (FUIWindowEntry* Entry = WindowMap.Find(WindowType))
    {
        if (Entry->Widget)
        {
            Entry->Widget->SetVisibility(ESlateVisibility::Collapsed);
            Entry->bActive = false;
            Entry->LastActiveTime = GetWorld()->GetTimeSeconds();
        }
    }
}