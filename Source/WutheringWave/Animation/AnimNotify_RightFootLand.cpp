// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_RightFootLand.h"
#include "Interface/WWFootLandCheckInterface.h"

void UAnimNotify_RightFootLand::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp)
		return;

	IWWFootLandCheckInterface* AnimInstance = Cast<IWWFootLandCheckInterface>(MeshComp->GetAnimInstance());
	if (!AnimInstance)
		return;

	AnimInstance->RightFootLand();
}
