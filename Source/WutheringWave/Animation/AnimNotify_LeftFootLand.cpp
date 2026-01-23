// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_LeftFootLand.h"
#include "Interface/WWFootLandCheckInterface.h"

void UAnimNotify_LeftFootLand::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp)
		return;

	IWWFootLandCheckInterface* AnimInstance = Cast<IWWFootLandCheckInterface>(MeshComp->GetAnimInstance());
	if (!AnimInstance)
		return;

	AnimInstance->LeftFootLand();
}
