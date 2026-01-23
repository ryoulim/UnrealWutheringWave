// Fill out your copyright notice in the Description page of Project Settings.


#include "WWButtonInSlideWidget.h"
#include "Components/Image.h"

void UWWButtonInSlideWidget::CheckButton(const FVector2D& ScreenMousePos)
{
    if (GetCachedGeometry().IsUnderLocation(ScreenMousePos))
    {
        OnButtonClicked.Broadcast(ButtonID);
    }
}
