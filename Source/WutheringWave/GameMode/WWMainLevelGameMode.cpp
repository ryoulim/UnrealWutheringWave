// Fill out your copyright notice in the Description page of Project Settings.


#include "WWMainLevelGameMode.h"
#include "Role/WWRoleBase.h"

AWWMainLevelGameMode::AWWMainLevelGameMode()
{
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerRef(TEXT("/Script/Engine.Blueprint'/Game/WutheringWaves/BluePrint/BP_WWPlayerController.BP_WWPlayerController_C'"));
	if (PlayerControllerRef.Class)
	{
		PlayerControllerClass = PlayerControllerRef.Class;
	}

	DefaultPawnClass = AWWRoleBase::StaticClass();
	
	// 멀티플레이어 설정
	bUseSeamlessTravel = true; // 원활한 레벨 전환
}

void AWWMainLevelGameMode::RestartPlayer(AController* NewPlayer)
{
	Super::RestartPlayer(NewPlayer);

	// PlayerStart가 없을 때 스폰 높이 보정 (검은 화면/지하 스폰 방지)
	APawn* Pawn = NewPlayer ? NewPlayer->GetPawn() : nullptr;
	if (Pawn && GetWorld())
	{
		const FVector Loc = Pawn->GetActorLocation();
		if (Loc.Z < -100.f)
		{
			Pawn->SetActorLocation(FVector(Loc.X, Loc.Y, 100.f), false, nullptr, ETeleportType::TeleportPhysics);
		}
	}
}
