// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
#include "InputActionValue.h"
#include "Interface/WWMenuInterface.h"
#include "Interface/WWInputStateCheckInterface.h"
#include "WWPlayerController.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogWWPlayerController, Log, All)

/**
 * 
 */
UCLASS()
class WUTHERINGWAVE_API AWWPlayerController : public APlayerController, public IWWMenuInterface, public IWWInputStateCheckInterface
{
	GENERATED_BODY()

public:
	AWWPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	/** 클라이언트에서 복제된 Pawn이 설정될 때 뷰 타깃을 맞춰 검은 화면 방지 */
	virtual void OnRep_Pawn() override;
	/** Add Another Client 시 뷰 타깃이 늦게 붙을 수 있어 지연 후 한 번 더 설정 */
	void EnsureClientViewTarget();

	/* InputStateCheck */
public:
	virtual bool IsMoveTriggerdThisFrame() const override {
		return bMoveTriggerdThisFrame;
	}

	/* PlayerPawn */
protected:
	/* 최초 Pawn 설정 */
	void InitPlayerPawn(int32 Index);
	/* 이 캐릭터를 생성하여 이 플레이어컨트롤러에 붙여라 */
	void CreatePlayerPawn(int32 RoleID, int32 PartyIndex);
	/* 캐릭터 전환용 */
	void ChangePlayerPawn(int32 Index);
	/** 서버는 CurrentParty[Index], 클라이언트는 GetPawn() 반환 */
	class AWWRoleBase* GetControlledRole() const;
	/* 파티 캐릭터를 저장해둘 배열 */
	UPROPERTY()
	TArray<TObjectPtr<class AWWRoleBase>> CurrentParty;
	/* 현재 선택된 캐릭터의 인덱스 */
	int32 CurrentPlayerPawnIndex{};

	/* Input */
protected:
	// 게임 입력 매핑 컨텍스트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|MappingContext")
	TObjectPtr<class UInputMappingContext> GameMappingContext;

	// 메뉴 토글
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Menu")
	TObjectPtr<class UInputAction> MenuToggleAction;

	// 이동 입력 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Move")
	TObjectPtr<class UInputAction> NormalMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Move")
	TObjectPtr<class UInputAction> NormalLookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Move")
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Move")
	TObjectPtr<class UInputAction> DashAction;

	void OnNormalMoveActionStarted();
	void OnNormalMoveActionTriggered(const FInputActionValue& Value);
	void OnNormalMoveActionCompleted();
	bool bMoveTriggerdThisFrame;

	void OnNormalLookActionTriggered(const FInputActionValue& Value);
	void OnJumpActionStarted();
	void OnJumpActionCompleted();
	void OnDashActionStarted();

	// 공격 입력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Attack")
	TObjectPtr<class UInputAction> NormalAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Attack")
	TObjectPtr<class UInputAction> SpecialAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Attack")
	TObjectPtr<class UInputAction> EcoAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Attack")
	TObjectPtr<class UInputAction> UltimateAttackAction;

	void OnNormalAttackActionStarted();
	void OnSpecialAttackActionStarted();
	void OnEcoAttackActionStarted();
	void OnUltimateAttackActionStarted();

	/** 멀티플레이어: 클라이언트가 호출하면 서버에서 실제 파티 전환 수행 */
	UFUNCTION(Server, Reliable)
	void ServerChangePartyIndex(int32 Index);

	// 캐릭터 전환하기
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|ChangePlayerPawn")
	TObjectPtr<class UInputAction> ChangePlayerPawnAction1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|ChangePlayerPawn")
	TObjectPtr<class UInputAction> ChangePlayerPawnAction2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|ChangePlayerPawn")
	TObjectPtr<class UInputAction> ChangePlayerPawnAction3;

	void OnChangePlayerPawnAction1Started();
	void OnChangePlayerPawnAction2Started();
	void OnChangePlayerPawnAction3Started();

	/* Menu */
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Menu)
	TSubclassOf<class UWWMenuWidget> MenuWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Menu)
	TObjectPtr<class UWWMenuWidget> MenuWidget;

	FTimerHandle ClientViewTargetTimerHandle;

	virtual void OpenMenu() override;
	virtual void CloseMenu() override;
};
