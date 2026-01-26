// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Headers/WWEnums.h"
#include "WWPreviewRenderer.generated.h"

class USceneCaptureComponent2D;
class UStaticMeshComponent;
class UCameraComponent;
class UTextureRenderTarget2D;

UCLASS()
class WUTHERINGWAVE_API AWWPreviewRenderer : public AActor
{
	GENERATED_BODY()
	
public:	
	AWWPreviewRenderer();

protected:
	virtual void Tick(float InTimeDelta) override;

	// === Functions ===
public:
	void SetPreviewRole(AActor* InActor);
	void CreateRenderTarget();
	class UTextureRenderTarget2D* GetRenderTarget() const;
	void Capture();

protected:

	// === Components ===
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AActor> CapturedRole;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneCaptureComponent2D> SceneCapture;

	UPROPERTY(EditDefaultsOnly, Category = "Setting|RenderTarget")
	int32 RenderTargetWidth = { 1920 };

	UPROPERTY(EditDefaultsOnly, Category = "Setting|RenderTarget")
	int32 RenderTargetHeight = { 1080 };
};
