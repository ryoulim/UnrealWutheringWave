// Fill out your copyright notice in the Description page of Project Settings.


#include "WWSlideWidget.h"
#include "Components/PanelWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

#include "Headers/WWMacros.h"

FReply UWWSlideWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		return FReply::Handled()
			.CaptureMouse(GetCachedWidget().ToSharedRef())
			.DetectDrag(GetCachedWidget().ToSharedRef(), EKeys::LeftMouseButton);
	}

	return FReply::Unhandled();
}

void UWWSlideWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	DragStartEvent(InMouseEvent);
}

FReply UWWSlideWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	DragEvent(InMouseEvent);
	return FReply::Unhandled();
}

FReply UWWSlideWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (EKeys::LeftMouseButton == InMouseEvent.GetEffectingButton())
	{
		if(bIsDragging)
		{
			DragEndEvent(InMouseEvent);
		}
		else
		{
			CheckButtons(InMouseEvent.GetScreenSpacePosition());
		}

		return FReply::Handled().ReleaseMouseCapture();
	}
	return FReply::Unhandled();
}

void UWWSlideWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	if (bIsStopping && !bIsDragging)
	{
		switch (DragEndAction)
		{
		case ESlideWidgetDragEndActionType::Intertia:
			UpdateInertia(DeltaTime);
			break;
		case ESlideWidgetDragEndActionType::Snapping:
			UpdateSnapping(DeltaTime);
			break;
		default:
			bIsStopping = false;
			break;
		}
	}
}

void UWWSlideWidget::NativeOnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent)
{
	Super::NativeOnMouseCaptureLost(CaptureLostEvent);

	if (bIsDragging)
	{
		ForceEndDrag();
	}
}

void UWWSlideWidget::ForceEndDrag()
{
	if (!bIsDragging)
		return;

	bIsDragging = false;
	bIsStopping = true;

	// 마우스 캡처 해제
	if (HasMouseCapture())
	{
		FSlateApplication::Get().ReleaseAllPointerCapture();
	}
}

void UWWSlideWidget::CheckButtons(const FVector2D& InMousePosition)
{
	for (auto& Button : Buttons)
	{
		Button->CheckButton(InMousePosition);
	}
}

void UWWSlideWidget::DragStartEvent(const FPointerEvent& InMouseEvent)
{
	bIsDragging = true;
	bIsStopping = false;

	LastPointerPos = InMouseEvent.GetScreenSpacePosition();
	//Velocity = FVector2D::Zero();

	RootWIndowSize = GetCachedGeometry().GetLocalSize();

	MinPos.X = RootWIndowSize.X - SlideWidth;
	MinPos.Y = RootWIndowSize.Y - SlideHeight;

	MinPos.X = FMath::Min(MinPos.X, 0.f);
	MinPos.Y = FMath::Min(MinPos.Y, 0.f);
}

void UWWSlideWidget::DragEvent(const FPointerEvent& InMouseEvent)
{
	if (!bIsDragging)
		return;

	FVector2D CurrentPos = InMouseEvent.GetScreenSpacePosition();
	FVector2D Delta = CurrentPos - LastPointerPos;
	LastPointerPos = CurrentPos;

	ApplyDragType(Delta);
	MoveContent(Delta);

	float DeltaTime = GetWorld()->GetDeltaSeconds();
	DragVelocity = Delta / DeltaTime;

	//GEngine->AddOnScreenDebugMessage(-1, 0.f,
	//	FColor::Green,
	//	FString::Printf(TEXT("VelocityOnDragEvent: %s"), *DragVelocity.ToString()));
}

void UWWSlideWidget::DragEndEvent(const FPointerEvent& InMouseEvent)
{
	bIsDragging = false;
	bIsStopping = true;
}

void UWWSlideWidget::MoveContent(const FVector2D& MoveDelta)
{
	if (!SlideWindow)
		return;

	UCanvasPanelSlot* PanelSlot =
		Cast<UCanvasPanelSlot>(SlideWindow->Slot);

	FVector2D Pos = PanelSlot->GetPosition();

	Pos += MoveDelta;

	Pos.X = FMath::Clamp(Pos.X, MinPos.X, 0.f);
	Pos.Y = FMath::Clamp(Pos.Y, MinPos.Y, 0.f);

	//WWPRINTF(TEXT("Pos: %s"), *Pos.ToString());
	//WWPRINTF(TEXT("MinPos: %s"), *MinPos.ToString());

	PanelSlot->SetPosition(Pos);
}

void UWWSlideWidget::UpdateInertia(float DeltaTime)
{
	if (DragVelocity.SquaredLength() < FMath::Square(MinVelocity))
	{
		bIsStopping = false;
		return;
	}

	DragVelocity.X = FMath::FInterpTo(DragVelocity.X, 0.f, DeltaTime, Damping);
	DragVelocity.Y = FMath::FInterpTo(DragVelocity.Y, 0.f, DeltaTime, Damping);

	FVector2D Delta = DragVelocity * DeltaTime;
	ApplyDragType(Delta);
	MoveContent(Delta);
}

void UWWSlideWidget::UpdateSnapping(float DeltaTime)
{
	if (!SlideWindow)
		return;

	UCanvasPanelSlot* PanelSlot =
		Cast<UCanvasPanelSlot>(SlideWindow->Slot);

	if (!PanelSlot)
		return;

	FVector2D CurrentPos = PanelSlot->GetPosition();
	FVector2D TargetPos = CurrentPos;

	// 가로 스냅
	if (bIsHorizonAble)
	{
		const float PageIndex =
			FMath::RoundToFloat(CurrentPos.X / RootWIndowSize.X);

		TargetPos.X = PageIndex * RootWIndowSize.X;
	}

	// 세로 스냅
	if (bIsVerticalAble)
	{
		const float PageIndex =
			FMath::RoundToFloat(CurrentPos.Y / RootWIndowSize.Y);

		TargetPos.Y = PageIndex * RootWIndowSize.Y;
	}

	// Clamp
	TargetPos.X = FMath::Clamp(TargetPos.X, MinPos.X, 0.f);
	TargetPos.Y = FMath::Clamp(TargetPos.Y, MinPos.Y, 0.f);

	FVector2D NewPos;
	NewPos.X = FMath::FInterpTo(CurrentPos.X, TargetPos.X, DeltaTime, SnapInterpSpeed);
	NewPos.Y = FMath::FInterpTo(CurrentPos.Y, TargetPos.Y, DeltaTime, SnapInterpSpeed);

	PanelSlot->SetPosition(NewPos);

	// 종료 판정
	if (FVector2D::Distance(NewPos, TargetPos) < SnapFinishThreshold)
	{
		PanelSlot->SetPosition(TargetPos);
		bIsStopping = false;
	}
}

void UWWSlideWidget::ApplyDragType(FVector2D& Vector)
{
	if (!bIsHorizonAble)
	{
		Vector.X = 0.f;
	}
	if (!bIsVerticalAble)
	{
		Vector.Y = 0.f;
	}
}
