// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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

	/* InputStateCheck */
public:
	virtual bool IsMoveTriggerdThisFrame() const override {
		return bMoveTriggerdThisFrame;
	}

	/* PlayerPawn */
protected:
	/* 최초 Pawn 설정 */
	void InitPlayerPawn(int32 Index);
	/* 이 플레이어를 만들어서 이 파티인덱스에 넣어라 */
	void CreatePlayerPawn(int32 RoleID, int32 PartyIndex);
	/* 캐릭터 스왑용 */
	void ChangePlayerPawn(int32 Index);
	/* 파티 캐릭터를 넣어둔 컨테이너 */
	UPROPERTY()
	TArray<TObjectPtr<class AWWRoleBase>> CurrentParty;
	/* 현재 선택한 캐릭터의 인덱스 */
	int32 CurrentPlayerPawnIndex{};

	/* Input */
protected:
	// 메인 매핑 컨텍스트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|MappingContext")
	TObjectPtr<class UInputMappingContext> GameMappingContext;

	// 메뉴 버튼
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Menu")
	TObjectPtr<class UInputAction> MenuToggleAction;

	// 이동관련 
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

	// 공격 관련
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

	// 캐릭터 바꾸기
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

	virtual void OpenMenu() override;
	virtual void CloseMenu() override;
};
