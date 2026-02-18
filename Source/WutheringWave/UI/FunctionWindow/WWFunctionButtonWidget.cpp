// Fill out your copyright notice in the Description page of Project Settings.


#include "WWFunctionButtonWidget.h"
#include "Components/RetainerBox.h"

void UWWFunctionButtonWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (bIsAppear)
    {
        AppearTimeAcc += InDeltaTime;
        float fRatio{};

        if (AppearTimeAcc >= Duration)
        {
            bIsAppear = false;
            fRatio = 1.f;
        }
        else
        {
            fRatio = AppearTimeAcc / Duration;
        }

        FlipRetainerBox->GetEffectMaterial()->SetScalarParameterValue(TEXT("TimeAcc"), fRatio);
        SetRenderOpacity(fRatio);
    }
}

void UWWFunctionButtonWidget::SetAppear(bool InAppear)
{
    bIsAppear = InAppear;
    AppearTimeAcc = 0.f;
    SetRenderOpacity(0.f);
}
