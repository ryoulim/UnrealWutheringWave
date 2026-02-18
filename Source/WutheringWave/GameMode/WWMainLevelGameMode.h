// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WWMainLevelGameMode.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVE_API AWWMainLevelGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AWWMainLevelGameMode();

	/** 멀티플레이어: 클라이언트 접속 시 Pawn 스폰 및 스폰 위치 보정 */
	virtual void RestartPlayer(AController* NewPlayer) override;
};
