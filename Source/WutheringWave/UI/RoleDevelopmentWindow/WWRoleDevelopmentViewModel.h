#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameData/DataTable/WWCharacterStatTable.h"
#include "WWRoleDevelopmentViewModel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRoleDataUpdated, int32, RoleID, int32, WeaponID, EWWWeaponTypeName, WeaponType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPreviewUpdated, class UTextureRenderTarget2D*, RenderTarget);

/**
 * MVVM Pattern: ViewModel for Role Development Window
 * Handles all business logic and subsystem interactions.
 */
UCLASS(BlueprintType, Blueprintable)
class WUTHERINGWAVE_API UWWRoleDevelopmentViewModel : public UObject
{
	GENERATED_BODY()

public:
	// 초기화 (게임 인스턴스/월드 참조용)
	void InitializeViewModel(UObject* InWorldContextObject);

	// 정리 (모델 소멸시)
	void DeinitializeViewModel();

	// 가장 처음 로드될 때 (현재 선택된 캐릭터) 호출
	void LoadInitialData();

	// 특정 다른 캐릭터를 선택했을 때
	void ChangeRole(int32 RoleID);

public:
	// 상태가 변경되었을 때 View에게 알리기 위한 델리게이트 (Events)
	UPROPERTY(BlueprintAssignable, Category = "ViewModel|Events")
	FOnRoleDataUpdated OnRoleDataUpdated;

	UPROPERTY(BlueprintAssignable, Category = "ViewModel|Events")
	FOnPreviewUpdated OnPreviewUpdated;

private:
	// 데이터 로드 종료 콜백
	void OnMainLoadEnd();
	
	// 내부 상태 갱신 로직
	void UpdateDataAndBroadcast();

private:
	UPROPERTY()
	UObject* WorldContextObject;

	int32 CurrentRoleID;
};
