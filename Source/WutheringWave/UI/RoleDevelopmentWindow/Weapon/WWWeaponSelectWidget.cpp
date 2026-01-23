// Fill out your copyright notice in the Description page of Project Settings.


#include "WWWeaponSelectWidget.h"
#include "Components/PanelWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "WWWeaponSelectButton.h"

#include "Subsystem/WWSaveDataSubsystem.h"
#include "GameData/SaveGame/WWWeaponDevelopmentData.h"

void UWWWeaponSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!ButtonClass || !SlideWindow)
		return;

	auto SubSystem = GetGameInstance()->GetSubsystem<UWWSaveDataSubsystem>();

	if (SubSystem)
	{
		const UWWWeaponDevelopmentSaveGame* WeaponSaveGameInstance = SubSystem->GetWeaponSaveGame();

		int32 Index{};
		Buttons.Reset();

		for (auto& Weapon : WeaponSaveGameInstance->WeaponMap)
		{
			UWWWeaponSelectButton* WeaponWidget = CreateWidget<UWWWeaponSelectButton>(GetOwningPlayer(), ButtonClass);
			WeaponWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

			WeaponWidget->SetImage(Weapon.Value.WeaponID);
			Buttons.Add(WeaponWidget);
		}
	}

	//SlideWidth = GetCachedGeometry().GetLocalSize().X;
}

void UWWWeaponSelectWidget::UpdateWindowbyType(EWWWeaponTypeName InType)
{
	/* 버튼중 현재 타입의 맞는 무기만 골라서 버튼들을 재정렬 */
	ActiveButtons.Reset();
	SlideWindow->ClearChildren();

	int32 Index{};

	for (auto& Button : Buttons)
	{
		UWWWeaponSelectButton* WeaponButton = Cast<UWWWeaponSelectButton>(Button);

		if (WeaponButton && WeaponButton->GetWeapontype() == InType)
		{
			ActiveButtons.Add(WeaponButton);
			SlideWindow->AddChild(WeaponButton);

			UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(WeaponButton->Slot);
			if (PanelSlot)
			{
				float AnchorPosX = (1.f / 3.3) * (Index % 3);
				PanelSlot->SetAnchors(FAnchors(AnchorPosX, 0.f, AnchorPosX, 0.f));

				float YPos = (Index/3) * (ItemSize + ItemSpacing);

				// Y는 고정 높이 + 아래로 정렬
				PanelSlot->SetOffsets(
					FMargin(
						0.f,       // Left
						YPos,      // Top
						ItemSize,// Right
						ItemSize // Height
					));

				PanelSlot->SetAlignment(FVector2D(0.f, 0.f));
			}
			Index++;
		}
	}

	SlideHeight = (Index / 3 + 1) * (ItemSize + ItemSpacing);
	UCanvasPanelSlot* SlideSlot = Cast<UCanvasPanelSlot>(SlideWindow->Slot);
	if(SlideSlot)
	{
		SlideSlot->SetOffsets(
			FMargin(
				0.f,       // Left
				0.f,      // Top
				0.f,       // Right
				SlideHeight  // Height
			));
	}
}

void UWWWeaponSelectWidget::CheckButtons(const FVector2D& InMousePosition)
{
	for (auto& Button : ActiveButtons)
	{
		Button->CheckButton(InMousePosition);
	}
}
