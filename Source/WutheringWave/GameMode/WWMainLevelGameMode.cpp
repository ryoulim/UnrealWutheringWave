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
}
