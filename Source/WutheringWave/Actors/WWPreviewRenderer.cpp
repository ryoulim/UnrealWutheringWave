// Fill out your copyright notice in the Description page of Project Settings.


#include "WWPreviewRenderer.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetRenderingLibrary.h"

// Sets default values
AWWPreviewRenderer::AWWPreviewRenderer()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Root);
	Camera->SetRelativeLocation(FVector(150.f, 0.f, 50.f));
	Camera->SetRelativeRotation(FRotator(-10.f, 180.f, 0.f));

	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
	SceneCapture->SetupAttachment(Camera);

	// === SceneCapture 기본 설정 ===
	SceneCapture->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
	SceneCapture->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
	SceneCapture->bCaptureEveryFrame = false;
	SceneCapture->ShowFlags.Cloud = false;
	SceneCapture->ShowFlags.Fog = false;
	SceneCapture->ShowFlags.VolumetricFog = false;
	SceneCapture->ShowFlags.Atmosphere = false;
	SceneCapture->ShowFlags.SkyLighting = false;
}

void AWWPreviewRenderer::Tick(float InTimeDelta)
{
	Super::Tick(InTimeDelta);
	Capture();
}

void AWWPreviewRenderer::SetPreviewRole(AActor* InActor)
{
	if (!SceneCapture)
	{
		return;
	}

	if (!InActor || !IsValid(InActor))
	{
		return;
	}

	SceneCapture->ShowOnlyActors.Reset();
	SceneCapture->ShowOnlyActors.Add(this);
	SceneCapture->ShowOnlyActors.Add(InActor);
	CapturedRole = InActor;

	// Actor 설정 후 즉시 캡쳐 시도
	// 하지만 애니메이션이 준비되지 않았을 수 있으므로 다음 프레임에도 캡쳐됨 (Tick에서)
}

void AWWPreviewRenderer::CreateRenderTarget()
{
	UTextureRenderTarget2D* PreviewRenderTarget = NewObject<UTextureRenderTarget2D>(this);
	PreviewRenderTarget->InitCustomFormat(RenderTargetWidth, RenderTargetHeight, PF_B8G8R8A8, false);
	PreviewRenderTarget->ClearColor = FLinearColor(0, 0, 1, 0);
	PreviewRenderTarget->UpdateResourceImmediate(true);

	if (SceneCapture && PreviewRenderTarget)
	{
		SceneCapture->TextureTarget = PreviewRenderTarget;
	}
}

UTextureRenderTarget2D* AWWPreviewRenderer::GetRenderTarget() const
{
	return SceneCapture->TextureTarget;
}

void AWWPreviewRenderer::Capture()
{
	if (!SceneCapture || !SceneCapture->TextureTarget)
	{
		return;
	}

	// CapturedRole이 유효한지 확인
	if (!CapturedRole || !IsValid(CapturedRole))
	{
		return;
	}

	UKismetRenderingLibrary::ClearRenderTarget2D(
		this,
		SceneCapture->TextureTarget,
		FLinearColor(0, 0, 0, 0));

	SceneCapture->CaptureScene();
}