// Fill out your copyright notice in the Description page of Project Settings.


#include "WWRoleDevActor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PointLightComponent.h"
#include "Animation/WWRoleDevAnimInstance.h"
#include "Kismet/KismetRenderingLibrary.h"

// Sets default values
AWWRoleDevActor::AWWRoleDevActor()
{
	PrimaryActorTick.bCanEverTick = false;

	CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	CharacterMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	CharacterMesh->SetVisibility(true);
	CharacterMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CharacterMesh->SetSimulatePhysics(false);
	CharacterMesh->SetLightingChannels(false, true, false);
	SetRootComponent(CharacterMesh);
}

void AWWRoleDevActor::SetPose(EWWUIAnimName InPoseName)
{
	if (UWWRoleDevAnimInstance* AnimInstance = Cast<UWWRoleDevAnimInstance>(CharacterMesh->GetAnimInstance()))
	{
		AnimInstance->SetTargetAnim(InPoseName);
	}

	/* 여기서 프롭을 포지션 바꿔줘야함 */
	for (int32 i = 0; i < PropMeshs.Num(); ++i)
	{
		if (UWWRoleDevAnimInstance* AnimInstance = Cast<UWWRoleDevAnimInstance>(PropMeshs[i]->GetAnimInstance()))
		{
			AnimInstance->SetTargetAnim(InPoseName);
		}
	}
}

void AWWRoleDevActor::SetDataAsset(const UWWRoleDataAsset* InDataAsset)
{
	DataAsset = InDataAsset;
}

void AWWRoleDevActor::ResetAnimation()
{
	if (UWWRoleDevAnimInstance* AnimInstance = Cast<UWWRoleDevAnimInstance>(CharacterMesh->GetAnimInstance()))
	{
		AnimInstance->SetReStartAnim(true);
	}

	/* 여기서 프롭을 포지션 바꿔줘야함 */
	for (int32 i = 0; i < PropMeshs.Num(); ++i)
	{
		if (UWWRoleDevAnimInstance* AnimInstance = Cast<UWWRoleDevAnimInstance>(PropMeshs[i]->GetAnimInstance()))
		{
			AnimInstance->SetReStartAnim(true);
		}
	}
}

void AWWRoleDevActor::CreateProps()
{
	/* 여기서 프롭 생성 필요함 */
	if (DataAsset)
	{
		/* 캐릭터매쉬 애님셋 넣어주기*/
		if (UWWRoleDevAnimInstance* AnimInstance = Cast<UWWRoleDevAnimInstance>(CharacterMesh->GetAnimInstance()))
		{
			AnimInstance->ReadyAnimSet(DataAsset->AnimSets);
		}

		for (auto& Prop : DataAsset->Props)
		{
			auto NewProp = NewObject<USkeletalMeshComponent>(this);

			// 1. Mesh
			NewProp->SetSkeletalMesh(Prop->Mesh.Get());

			// 2. Animation Mode
			NewProp->SetAnimationMode(EAnimationMode::AnimationBlueprint);

			// 3. Attach
			NewProp->SetupAttachment(CharacterMesh);

			// 4. Register
			NewProp->RegisterComponent();

			// 5. AnimInstanceClass 지정 (이 시점 중요)
			NewProp->SetAnimInstanceClass(PreviewAnimInstance);
			if (UWWRoleDevAnimInstance* AnimInstance = Cast<UWWRoleDevAnimInstance>(NewProp->GetAnimInstance()))
			{
				AnimInstance->ReadyAnimSet(Prop->AnimSets);
			}

			// 6. 기타 설정
			NewProp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			NewProp->SetSimulatePhysics(false);
			NewProp->SetLightingChannels(false, true, false);

			PropMeshs.Add(NewProp);
		}
	}
}
