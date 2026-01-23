// Fill out your copyright notice in the Description page of Project Settings.


#include "WWRoleSlideWidget.h"
#include "Components/PanelWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

#include "WWRoleDevelopHeadWidget.h"
#include "Subsystem/WWSaveDataSubsystem.h"
#include "GameData/SaveGame/WWCharacterDevelopmentData.h"


void UWWRoleSlideWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!ButtonClass || !SlideWindow)
		return;

	/* 세이브 데이터 기준으로 현재 가지고 있는 캐릭터 풀만큼 로고를 동적으로 생성해줘야 함 */
	auto Subsystem = GetGameInstance()->GetSubsystem<UWWSaveDataSubsystem>();

	if (Subsystem)
	{
		const UWWCharacterDevelopmentSaveGame* CharacterSaveGameInstance = Subsystem->GetCharacterSaveGame();

		int32 Index{};
		Buttons.Reset();

		for (auto& Role : CharacterSaveGameInstance->CharacterMap)
		{
			UWWRoleDevelopHeadWidget* HeadWidget = CreateWidget<UWWRoleDevelopHeadWidget>(GetOwningPlayer(), ButtonClass);
			SlideWindow->AddChild(HeadWidget);
			Buttons.Add(HeadWidget);

			UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(HeadWidget->Slot);

			if (PanelSlot)
			{
				// X는 부모에 꽉 차게
				PanelSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 0.f));

				float YPos = Index * (ItemHeight + ItemSpacing);

				// Y는 고정 높이 + 아래로 정렬
				PanelSlot->SetOffsets(
					FMargin(
						0.f,       // Left
						YPos,      // Top
						0.f,       // Right
						ItemHeight // Height
					));

				PanelSlot->SetAlignment(FVector2D(0.f, 0.f));
			}
			Index++;
		}

		SlideHeight = Index * (ItemHeight + ItemSpacing);
		UCanvasPanelSlot* SlideSlot = Cast<UCanvasPanelSlot>(SlideWindow->Slot);

		SlideSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 0.f));
		SlideSlot->SetOffsets(
			FMargin(
				0.f,       // Left
				0.f,      // Top
				0.f,       // Right
				SlideHeight  // Height
			));
	}
}

void UWWRoleSlideWidget::SetButtonImage()
{
	auto Subsystem = GetGameInstance()->GetSubsystem<UWWSaveDataSubsystem>();

	if (Subsystem)
	{
		const UWWCharacterDevelopmentSaveGame* CharacterSaveGameInstance = Subsystem->GetCharacterSaveGame();
		if (CharacterSaveGameInstance->CharacterMap.Num() != Buttons.Num())
			return;

		int32 Index{};
		for (auto& Role : CharacterSaveGameInstance->CharacterMap)
		{
			Cast<UWWRoleDevelopHeadWidget>(Buttons[Index])->SetRoleImage(Role.Key);
			Index++;
		}
	}
}
