// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Headers/WWEnums.h"
#include "WWRoleDevActor.generated.h"

UCLASS()
class WUTHERINGWAVE_API AWWRoleDevActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AWWRoleDevActor();

	/* 기능함수들 */
public:
	/* 포지션 바꾸기 */
	void SetPose(EWWUIAnimName InPoseName);
	/* 데이터 에셋 넣기 */
	void SetDataAsset(const class UWWRoleDataAsset* InDataAsset);
	/* 애니메이션 초기화 */
	void ResetAnimation();
	/* Prop 생성 */
	void CreateProps();

	/* Mesh */
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setting|Mesh")
	TObjectPtr<class USkeletalMeshComponent> CharacterMesh;

	UPROPERTY(BlueprintReadOnly, Category = "Setting|Mesh")
	TArray<TObjectPtr<class USkeletalMeshComponent>> PropMeshs;

	/* Data Asset */
protected:
	UPROPERTY()
	TObjectPtr<const class UWWRoleDataAsset> DataAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting|Anim")
	TSubclassOf<class UWWRoleDevAnimInstance> PreviewAnimInstance;
};
