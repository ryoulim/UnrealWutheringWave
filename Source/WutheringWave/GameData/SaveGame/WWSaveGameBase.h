// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"

#include "Engine/GameInstance.h"
#include "WWSaveGameBase.generated.h"

/**
 *
 */

UCLASS()
class WUTHERINGWAVE_API UWWSaveGameBase : public USaveGame
{
	GENERATED_BODY()

public:
	void SaveData()
	{
		UGameplayStatics::SaveGameToSlot(this, FileName, SlotNum);
	}
	
	template <typename T>
	static T* LoadData(const FString& InFileName, int32 InSlotNum, UGameInstance* GameInstance)
	{
		T* Instance = Cast<T>(UGameplayStatics::LoadGameFromSlot(InFileName, InSlotNum));
		if (!Instance)
		{
			Instance = NewObject<T>();
		}

		Instance->FileName = InFileName;
		Instance->SlotNum = InSlotNum;
		Instance->GameInstance = GameInstance;

		return Instance;
	}

protected:
	TObjectPtr<UGameInstance> GameInstance;

private:
	FString FileName;
	int32 SlotNum;
};