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
	
	// 멀티플레이어를 위한 Replication 설정
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/* Swap */
public:
	/* 필드 캐릭터로 전환했다. */
	virtual void OnField();
	/* 필드 캐릭터에서 나왔다. */
	virtual void OffField();
	/* 다른 캐릭터의 상태를 복사 */
	void CopyState(const ACharacter* Other);
	/* 캐릭터 활성화 상태 설정 */
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

	// 멀티플레이어를 위한 Server RPC
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerNormalAttack();
	
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSpecialAttack();
	
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerEcoAttack();
	
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerUltimateAttack();
	
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDash();

	// 클라이언트에서 호출하는 함수들 (서버 RPC로 전송)
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
