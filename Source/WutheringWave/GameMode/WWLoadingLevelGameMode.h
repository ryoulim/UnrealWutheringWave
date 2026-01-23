// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/AssetManager.h"
#include "WWLoadingLevelGameMode.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVE_API AWWLoadingLevelGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AWWLoadingLevelGameMode();

private:
	virtual void BeginPlay() override;

	/* 이 순서대로 체인로딩 */
private:
	void LoadGlobalAssets();
	void LoadPartyCharacter();

	void OnLoadEnd();

private:
	TSharedPtr<FStreamableHandle> StreamableHandle;
};
