// Fill out your copyright notice in the Description page of Project Settings.

#include "WWWindowBaseWidget.h"

FReply UWWWindowBaseWidget::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Tab)
	{
		OnWWWindowBaseCloseCall.Broadcast();
	}

	return FReply::Handled();
}