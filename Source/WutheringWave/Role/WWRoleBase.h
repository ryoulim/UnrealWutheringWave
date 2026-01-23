// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "WWRoleBase.generated.h"

UCLASS()
class WUTHERINGWAVE_API AWWRoleBase : public ACharacter
{
	GENERATED_BODY()
	
public:
	AWWRoleBase();

	/* Swap */
public:
	/* 지금 필드로 등장했다. */
	virtual void OnField();
	/* 지금 필드에서 나왔다. */
	virtual void OffField();
	/* 캐릭터 스왑시의 상태를 복사 */
	void CopyState(const ACharacter* Other);
	/* 월드에서 캐릭터 감추기 */
	void SetActive(bool bActive);

	UFUNCTION(BlueprintCallable)
	void SetSpeedRun();

	UFUNCTION(BlueprintCallable)
	void SetSpeedSprint();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting|Movement")
	float RunSpeed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting|Movement")
	float SprintSpeed = 1000.f;

	/* Action */
public:
	void NormalMoveStart();
	void NormalMove(const FInputActionValue& Value);
	void Dash();

	void NormalAttack();
	void SpecialAttack();
	void EcoAttack();
	void UltimateAttack();

	void SetUIMode(bool bInMode = true);

	/* Camera */
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setting|Camera")
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setting|Camera")
	TObjectPtr<class UCameraComponent> FollowCamera;

	/* RenderMesh */
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setting|RenderMesh")
	TObjectPtr<class USkeletalMeshComponent> RenderMesh;

	/* Props */
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting|Props")
	TArray<TObjectPtr<USkeletalMeshComponent>> PropMeshs;

	/* Data Asset */
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting|Data")
	TObjectPtr<const class UWWRoleDataAsset> DataAsset;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting|Flags")
	bool bIsUIMode = false;
};
