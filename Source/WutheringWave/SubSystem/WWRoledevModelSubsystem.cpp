// Fill out your copyright notice in the Description page of Project Settings.

#include "WWRoledevModelSubsystem.h"
#include "Engine/World.h"

#include "Actors/WWPreviewRenderer.h"
#include "Role/WWRoleDevActor.h"
#include "GameData/DataAsset/WWRoleDataAsset.h"

void UWWRoledevModelSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// 필요하면 여기서 RenderTarget 로드 / 초기화 가능
}

void UWWRoledevModelSubsystem::Deinitialize()
{
	ClosePreview();
	Super::Deinitialize();
}

void UWWRoledevModelSubsystem::OpenPreview()
{
	UWorld* World = GetWorld();

	if (!World || !PreviewActorClass)
		return;

	// 이미 PreviewRenderer가 존재하고 유효한 경우 재사용
	if (PreviewRenderer && IsValid(PreviewRenderer))
		return;

	// 기존 PreviewRenderer가 파괴되었거나 유효하지 않은 경우 정리
	if (PreviewRenderer && !IsValid(PreviewRenderer))
	{
		PreviewRenderer = nullptr;
	}

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	PreviewRenderer =
		World->SpawnActor<AWWPreviewRenderer>(
			PreviewActorClass,
			FTransform::Identity,
			Params);

	if (PreviewRenderer)
	{
		PreviewRenderer->CreateRenderTarget();
	}
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
	if (!PreviewRenderer || !IsValid(PreviewRenderer))
	{
		return nullptr;
	}
	return PreviewRenderer->GetRenderTarget();
}

void UWWRoledevModelSubsystem::SetPreviewRole(int32 RoleID)
{
	// PreviewRenderer가 없거나 유효하지 않으면 생성
	if (!PreviewRenderer || !IsValid(PreviewRenderer))
	{
		OpenPreview();
	}

	if (!PreviewRenderer || !IsValid(PreviewRenderer))
	{
		return;
	}

	TObjectPtr<class AWWRoleDevActor>& TargetRole = PreviewActors.FindOrAdd(RoleID);

	// Actor가 파괴되었거나 유효하지 않은 경우 재생성
	if (!TargetRole || !IsValid(TargetRole))
	{
		TargetRole = CreatePreviewRole(RoleID);
		if (!TargetRole)
		{
			return;
		}
	}

	// 기존 Actor든 새 Actor든 상관없이 애니메이션을 확실히 초기화
	// 창을 닫았다가 다시 열 때 상태가 초기화되도록 보장
	TargetRole->ResetAnimation();
	TargetRole->SetPose(EWWUIAnimName::Nature);

	CurrentActor = TargetRole;
	if (TargetRole && PreviewRenderer && IsValid(PreviewRenderer))
	{
		PreviewRenderer->SetPreviewRole(TargetRole);
		
		// 애니메이션이 시작될 시간을 주고 여러 프레임에 걸쳐 캡쳐 보장
		if (UWorld* World = GetWorld())
		{
			// 다음 프레임에 애니메이션 재시작 및 캡쳐
			World->GetTimerManager().SetTimerForNextTick([this, TargetRole]()
			{
				if (TargetRole && IsValid(TargetRole))
				{
					// 애니메이션을 다시 한 번 재시작하여 확실히 초기화
					TargetRole->ResetAnimation();
					TargetRole->SetPose(EWWUIAnimName::Nature);
				}
				
				if (PreviewRenderer && IsValid(PreviewRenderer))
				{
					PreviewRenderer->Capture();
				}
			});
			
			// 2프레임 후에도 캡쳐 (애니메이션이 확실히 진행된 후)
			FTimerHandle TimerHandle;
			World->GetTimerManager().SetTimer(TimerHandle, [this]()
			{
				if (PreviewRenderer && IsValid(PreviewRenderer))
				{
					PreviewRenderer->Capture();
				}
			}, 0.033f, false); // 약 2프레임 (60fps 기준)
		}
		
		// 즉시 캡쳐도 시도 (Tick에서도 계속 캡쳐되므로 문제없음)
		PreviewRenderer->Capture();
	}
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
			// PreviewClass가 유효한지 확인
			if (!Asset->PreviewClass)
			{
				UE_LOG(LogTemp, Warning, TEXT("WWRoleDataAsset PreviewClass is null for RoleID: %d"), RoleID);
				return nullptr;
			}

			NewActor = World->SpawnActor<AWWRoleDevActor>(
				Asset->PreviewClass,
				FTransform::Identity,
				Params);

			// SpawnActor가 실패했을 수 있으므로 null 체크
			if (!NewActor || !IsValid(NewActor))
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to spawn AWWRoleDevActor for RoleID: %d"), RoleID);
				return nullptr;
			}

			NewActor->SetActorRotation(FRotator(0.f, -90.f, 0.f));
			NewActor->SetDataAsset(Asset);
			NewActor->CreateProps();
			
			// CreateProps() 후 AnimInstance가 준비될 때까지 약간의 시간이 필요할 수 있음
			// 애니메이션 초기화는 SetPreviewRole에서 수행
			// (SetPose는 SetPreviewRole에서 호출됨)
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("WWRoleDataAsset not found for RoleID: %d"), RoleID);
		}
	}

	return NewActor;
}