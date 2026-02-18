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

	/* 이 레벨로 진입시 에셋 로드 */
private:
	void LoadGlobalAssets();
	void LoadPartyCharacter();

	void OnLoadEnd();

private:
	TSharedPtr<FStreamableHandle> StreamableHandle;
};
