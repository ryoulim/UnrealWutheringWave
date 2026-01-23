// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WWButtonInSlideWidget.h"
#include "WWSlideWidget.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ESlideWidgetDragEndActionType : uint8
{
    None,
    Intertia,
    Snapping,
};

UCLASS()
class WUTHERINGWAVE_API UWWSlideWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

    virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    virtual void NativeOnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;

    UFUNCTION(BlueprintCallable)
    void ForceEndDrag();

    virtual void CheckButtons(const FVector2D& InMousePosition);

protected:
    UPROPERTY(EditAnywhere, Category = "Setting")
    TSubclassOf<class UWWButtonInSlideWidget> ButtonClass;

    UPROPERTY(BlueprintReadOnly, Category = Buttons)
    TArray<TObjectPtr<class UWWButtonInSlideWidget>> Buttons{};

    /* Setting */
protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting")
    bool bIsHorizonAble;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting")
    bool bIsVerticalAble;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
    ESlideWidgetDragEndActionType DragEndAction;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    TObjectPtr<class UPanelWidget> SlideWindow;

    /* Drag & Move */
public:
    void DragStartEvent(const FPointerEvent& InMouseEvent);
    void DragEvent(const FPointerEvent& InMouseEvent);
    void DragEndEvent(const FPointerEvent& InMouseEvent);

protected:
    void MoveContent(const FVector2D& MoveDelta);

    bool bIsDragging{};
    bool bIsStopping{};
    FVector2D DragVelocity{};
    FVector2D LastPointerPos{};

    FVector2D MinPos{};
    float SlideHeight{};
    float SlideWidth{};
    FVector2D RootWIndowSize{};

    /* Inertia */
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting|Inertia")
    float Damping = 8.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting|Inertia")
    float MinVelocity = 5.f;

    void UpdateInertia(float DeltaTime);

    /* Snap */
protected:
    void UpdateSnapping(float DeltaTime);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting|Snapping")
    float SnapInterpSpeed = 12.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting|Snapping")
    float SnapFinishThreshold = 1.f;

    /* Utility*/
protected:
    void ApplyDragType(FVector2D& Vector);
};
