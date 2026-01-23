// Fill out your copyright notice in the Description page of Project Settings.


#include "WWFunctionSlideWindow.h"
#include "WWFunctionButtonWidget.h"

#include "Components/PanelWidget.h"
#include "Components/CanvasPanelSlot.h"

void UWWFunctionSlideWindow::NativeConstruct()
{
	Super::NativeConstruct();

	if (!ButtonClass || !SlideWindow)
		return;

	UCanvasPanelSlot* SlideSlot = Cast<UCanvasPanelSlot>(SlideWindow->Slot);
	SlideWidth = SlideSlot->GetOffsets().Right;
}

void UWWFunctionSlideWindow::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	UpdateAppear(InDeltaTime);
}

void UWWFunctionSlideWindow::Appear()
{
	bIsAppear = true;
	AppearTimeAcc = 0.f;
	LastAppearButtonIndex = -1;
}

void UWWFunctionSlideWindow::Disappear()
{
	bIsAppear = false;
	AppearTimeAcc = 0.f;

	for (auto& Button : Buttons)
	{
		auto WWButton = Cast<UWWFunctionButtonWidget>(Button);
		WWButton->SetAppear(false);
	}
}

void UWWFunctionSlideWindow::UpdateAppear(float DeltaTime)
{
	if (!bIsAppear)
		return;

	AppearTimeAcc += DeltaTime;

	int32 TargetIndex = static_cast<int32>(AppearTimeAcc / ButtonAppearInterval);
	if (TargetIndex != LastAppearButtonIndex)
	{
		for (int i = LastAppearButtonIndex + 1; i <= TargetIndex; ++i)
		{
			if (Buttons.Num() <= i)
			{
				bIsAppear = false;
				return;
			}
			Cast<UWWFunctionButtonWidget>(Buttons[i])->SetAppear(true);
		}

		LastAppearButtonIndex = TargetIndex;
	}
}