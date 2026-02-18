// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Headers/WWEnums.h"
#include "WWRoledevModelSubsystem.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class WUTHERINGWAVE_API UWWRoledevModelSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	// === Subsystem LifeCycle ===
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// === Preview Control ===
public:
	void OpenPreview();
	void ClosePreview();

	// === Accessors ===
public:
	class UTextureRenderTarget2D* GetRenderTarget() const;

	UFUNCTION(BlueprintCallable)
	void SetPreviewRole(int32 RoleID);

	UFUNCTION(BlueprintCallable)
	void SetPose(EWWUIAnimName PoseType);

protected:
	class AWWRoleDevActor* CreatePreviewRole(int32 RoleID);

	/* 액터들 */
protected :
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AWWPreviewRenderer> PreviewActorClass;

	UPROPERTY()
	TMap<int32, TObjectPtr<class AWWRoleDevActor>> PreviewActors;

	UPROPERTY()
	TObjectPtr<class AWWRoleDevActor> CurrentActor = { nullptr };

	/* 렌더러 */
	UPROPERTY()
	TObjectPtr<class AWWPreviewRenderer> PreviewRenderer = { nullptr };
};
