// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/WWCameraRigActor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AWWCameraRigActor::AWWCameraRigActor()
{
	PrimaryActorTick.bCanEverTick = false;

	bFindCameraComponentWhenViewTarget = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	/* 朝五虞 持失 */
	if (!CameraBoom)
	{
		CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
		CameraBoom->TargetArmLength = 400.0f;
		CameraBoom->SetupAttachment(RootComponent);
		CameraBoom->bUsePawnControlRotation = true;
	}

	if (!FollowCamera)
	{
		FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
		FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
		FollowCamera->bUsePawnControlRotation = false;
	}
}
