// Fill out your copyright notice in the Description page of Project Settings.

#include "WWRoledevModelSubsystem.h"
#include "Engine/World.h"

#include "Actors/WWPreviewRenderer.h"
#include "Role/WWRoleDevActor.h"
#include "GameData/DataAsset/WWRoleDataAsset.h"

void UWWRoledevModelSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// 필요하면 여기서 RenderTarget 로드 / 캐싱 가능
}

void UWWRoledevModelSubsystem::Deinitialize()
{
	ClosePreview();
	Super::Deinitialize();
}

void UWWRoledevModelSubsystem::OpenPreview()
{
	UWorld* World = GetWorld();

	/* 이미 열려있거나, 월드가 없는 비정상 상태 */
	if (!World || PreviewRenderer || !PreviewActorClass)
		return;

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	PreviewRenderer =
		World->SpawnActor<AWWPreviewRenderer>(
			PreviewActorClass,
			FTransform::Identity,
			Params);

	PreviewRenderer->CreateRenderTarget();
}

void UWWRoledevModelSubsystem::ClosePreview()
{
	if (PreviewRenderer)
	{
		PreviewRenderer->Destroy();
		PreviewRenderer = nullptr;
	}

	for (auto& [Key, Actor] : PreviewActors)
	{
		if (Actor)
		{
			Actor->Destroy();
		}
	}

	CurrentActor = nullptr;
	PreviewActors.Reset();
}

UTextureRenderTarget2D* UWWRoledevModelSubsystem::GetRenderTarget() const
{
	return PreviewRenderer->GetRenderTarget();
}

void UWWRoledevModelSubsystem::SetPreviewRole(int32 RoleID)
{
	TObjectPtr<class AWWRoleDevActor>& TargetRole = PreviewActors.FindOrAdd(RoleID);

	if (nullptr == TargetRole)
	{
		TargetRole = CreatePreviewRole(RoleID);
		TargetRole->SetPose(EWWUIAnimName::Nature);
	}
	else
	{
		TargetRole->ResetAnimation();
	}

	CurrentActor = TargetRole;
	PreviewRenderer->SetPreviewRole(TargetRole);
}

void UWWRoledevModelSubsystem::SetPose(EWWUIAnimName PoseType)
{
	if (CurrentActor)
	{
		CurrentActor->SetPose(PoseType);
	}
}

AWWRoleDevActor* UWWRoledevModelSubsystem::CreatePreviewRole(int32 RoleID)
{
	AWWRoleDevActor* NewActor = nullptr;

	if (UWorld* World = GetWorld())
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		if(auto Asset = UWWRoleDataAsset::Get(RoleID))
		{
			NewActor = World->SpawnActor<AWWRoleDevActor>(
				Asset->PreviewClass,
				FTransform::Identity,
				Params);

			NewActor->SetActorRotation(FRotator(0.f, -90.f, 0.f));
			NewActor->SetDataAsset(Asset);
			NewActor->CreateProps();
		}
	}

	return NewActor;
}