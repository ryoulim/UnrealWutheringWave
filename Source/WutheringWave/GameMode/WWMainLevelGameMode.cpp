// Fill out your copyright notice in the Description page of Project Settings.


#include "WWMainLevelGameMode.h"
#include "Role/WWRoleBase.h"
#include "Engine/World.h"
#include "Engine/NetDriver.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "IpNetDriver.h"
#include "OnlineSubsystemUtils.h"

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

void AWWMainLevelGameMode::BeginPlay()
{
	Super::BeginPlay();

	// 서버(Listen Server)일 때만: 리슨 포트 열렸는지 로그 (Add Another Client 타이밍 참고용)
	if (GetWorld() && GetWorld()->GetNetMode() == NM_ListenServer)
	{
		UNetDriver* NetDriver = GetWorld()->GetNetDriver();
		if (NetDriver)
		{
			if (UIpNetDriver* IpNetDriver = Cast<UIpNetDriver>(NetDriver))
			{
				if (FSocket* Socket = IpNetDriver->GetSocket())
				{
					TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
					Socket->GetAddress(*Addr);
					UE_LOG(LogTemp, Log, TEXT("[Server] Listen port ready: %s (Add Another Client 가능)"), *Addr->ToString(true));
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("[Server] Listen port: IpNetDriver has no socket"));
				}
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("[Server] MainLevel ready (NetDriver=%s, Add Another Client 가능)"), *GetNameSafe(NetDriver));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("[Server] MainLevel ready but NetDriver is null"));
		}
	}
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
