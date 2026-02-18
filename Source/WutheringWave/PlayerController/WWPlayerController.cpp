// Fill out your copyright notice in the Description page of Project Settings.


#include "WWPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"

#include "Role/WWRoleBase.h"
#include "UI/MainMenu/WWMenuWidget.h"

#include "SubSystem/WWDataTableIDSearchSubsystem.h"
#include "GameData/SaveGame/WWCharacterDevelopmentData.h"

#include "SubSystem/WWSaveDataSubsystem.h"
#include "GameData/DataAsset/WWRoleDataAsset.h"

#include "Actors/WWCameraRigActor.h"

DEFINE_LOG_CATEGORY(LogWWPlayerController)

AWWPlayerController::AWWPlayerController()
{
	/* MappingContext */
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> GameMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/WutheringWaves/Input/Menu/IMC_GamePlay.IMC_GamePlay'"));
	if (GameMappingContextRef.Succeeded())
	{
		GameMappingContext = GameMappingContextRef.Object;
	}

	/* Action */
	static ConstructorHelpers::FObjectFinder<UInputAction> MenuToggleActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/WutheringWaves/Input/Menu/IA_ToggleMenu.IA_ToggleMenu'"));
	if (MenuToggleActionRef.Succeeded())
	{
		MenuToggleAction = MenuToggleActionRef.Object;
	}
}

void AWWPlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();
	// 클라이언트에서 Pawn 복제 직후 뷰 타깃 설정 (Add Another Client 검은 화면 방지)
	if (GetPawn() && IsLocalController())
	{
		SetViewTarget(GetPawn());
	}
}

void AWWPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	// 멀티플레이어: SaveGame 로드는 서버에서만 수행
	// 클라이언트는 서버로부터 데이터를 받아야 함
	if (HasAuthority())
	{
		UWWSaveDataSubsystem* SaveDataSubsystem = GetGameInstance()->GetSubsystem<UWWSaveDataSubsystem>();
		SaveDataSubsystem->LoadAllData();
		auto CharacterSaveGame = SaveDataSubsystem->GetCharacterSaveGame();

		/* 파티 생성 */
		CurrentParty.SetNum(3);
		int32 PartyIndex{};
		for (auto& RoleIndex : CharacterSaveGame->PartyCharacter)
		{
			CreatePlayerPawn(RoleIndex, PartyIndex++);
		}
		InitPlayerPawn(CharacterSaveGame->CurrentPartyIndex);
	}

	/* Mapping Context - 모든 클라이언트에서 설정 */
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem && GameMappingContext)
	{
		Subsystem->AddMappingContext(GameMappingContext, 0);
	}

	/* Menu Widget - 모든 클라이언트에서 생성 */
	if (MenuWidgetClass)
	{
		MenuWidget = CreateWidget<UWWMenuWidget>(this, MenuWidgetClass);
		MenuWidget->AddToViewport();
		MenuWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	// 클라이언트: 이미 Pawn이 있으면 뷰 타깃 설정 (레벨 진입 직후 검은 화면 방지)
	if (IsLocalController() && GetPawn())
	{
		SetViewTarget(GetPawn());
	}
}

void AWWPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	// 메뉴 토글
	EnhancedInputComponent->BindAction(MenuToggleAction, ETriggerEvent::Started, this, &AWWPlayerController::OpenMenu);

	// 이동 입력 
	EnhancedInputComponent->BindAction(NormalMoveAction, ETriggerEvent::Started, this, &AWWPlayerController::OnNormalMoveActionStarted);
	EnhancedInputComponent->BindAction(NormalMoveAction, ETriggerEvent::Triggered, this, &AWWPlayerController::OnNormalMoveActionTriggered);
	EnhancedInputComponent->BindAction(NormalLookAction, ETriggerEvent::Triggered, this, &AWWPlayerController::OnNormalLookActionTriggered);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AWWPlayerController::OnJumpActionStarted);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AWWPlayerController::OnJumpActionCompleted);
	EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &AWWPlayerController::OnDashActionStarted);

	// 공격 입력
	EnhancedInputComponent->BindAction(NormalAttackAction, ETriggerEvent::Started, this, &AWWPlayerController::OnNormalAttackActionStarted);
	EnhancedInputComponent->BindAction(SpecialAttackAction, ETriggerEvent::Started, this, &AWWPlayerController::OnSpecialAttackActionStarted);
	EnhancedInputComponent->BindAction(EcoAttackAction, ETriggerEvent::Started, this, &AWWPlayerController::OnEcoAttackActionStarted);
	EnhancedInputComponent->BindAction(UltimateAttackAction, ETriggerEvent::Started, this, &AWWPlayerController::OnUltimateAttackActionStarted);

	// 캐릭터 전환
	EnhancedInputComponent->BindAction(ChangePlayerPawnAction1, ETriggerEvent::Started, this, &AWWPlayerController::OnChangePlayerPawnAction1Started);
	EnhancedInputComponent->BindAction(ChangePlayerPawnAction2, ETriggerEvent::Started, this, &AWWPlayerController::OnChangePlayerPawnAction2Started);
	EnhancedInputComponent->BindAction(ChangePlayerPawnAction3, ETriggerEvent::Started, this, &AWWPlayerController::OnChangePlayerPawnAction3Started);
}

void AWWPlayerController::InitPlayerPawn(int32 Index)
{
	if (!CurrentParty.IsValidIndex(Index) ||
		!CurrentParty[Index])
		return;

	AWWRoleBase* NewPlayerPawn = CurrentParty[Index];
	AWWRoleBase* OldPlayerPawn = Cast<AWWRoleBase>(GetPawn());

	FRotator PrevRot = GetControlRotation();

	CurrentPlayerPawnIndex = Index;
	Possess(NewPlayerPawn);

	SetControlRotation(PrevRot);

	OldPlayerPawn->Destroy();
	NewPlayerPawn->SetActive(true);

	NewPlayerPawn->CopyState(OldPlayerPawn);
}

void AWWPlayerController::CreatePlayerPawn(int32 RoleID, int32 PartyIndex)
{
	// 멀티플레이어: 서버에서만 Pawn 생성
	if (!HasAuthority())
	{
		return;
	}

	if (!CurrentParty.IsValidIndex(PartyIndex) || 
		RoleID == -1)
		return;

	if (CurrentParty[PartyIndex])
		CurrentParty[PartyIndex]->Destroy();

	const UWWRoleDataAsset* RoleAssetData = UWWRoleDataAsset::Get(RoleID);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = this; // PlayerController를 Owner로 설정

	CurrentParty[PartyIndex] = GetWorld()->SpawnActor<AWWRoleBase>(RoleAssetData->RoleClass, FTransform(FVector(0.f,0.f,-10000.f)), SpawnParams);
	check(CurrentParty[PartyIndex]);

	CurrentParty[PartyIndex]->SetActive(false);
}

void AWWPlayerController::ChangePlayerPawn(int32 Index)
{
	if (CurrentPlayerPawnIndex == Index)
		return;

	if (!CurrentParty.IsValidIndex(Index) ||
		!CurrentParty[Index])
		return;

	AWWRoleBase* NewPlayerPawn = CurrentParty[Index];
	AWWRoleBase* OldPlayerPawn = Cast<AWWRoleBase>(GetPawn());

	FRotator PrevRot = GetControlRotation();

	CurrentPlayerPawnIndex = Index;
	if (auto SaveDataSubsystem = GetGameInstance()->GetSubsystem<UWWSaveDataSubsystem>())
	{
		SaveDataSubsystem->GetCharacterSaveGame()->CurrentPartyIndex = Index;
	}
	Possess(NewPlayerPawn);

	SetControlRotation(PrevRot);

	OldPlayerPawn->OffField();
	NewPlayerPawn->OnField();

	NewPlayerPawn->CopyState(OldPlayerPawn);
}

void AWWPlayerController::OnNormalMoveActionStarted()
{
	if (!CurrentParty[CurrentPlayerPawnIndex])
		return;

	CurrentParty[CurrentPlayerPawnIndex]->NormalMoveStart();
	bMoveTriggerdThisFrame = true;
}

void AWWPlayerController::OnNormalMoveActionTriggered(const FInputActionValue& Value)
{
	if (!CurrentParty[CurrentPlayerPawnIndex])
		return;

	CurrentParty[CurrentPlayerPawnIndex]->NormalMove(Value);
}

void AWWPlayerController::OnNormalMoveActionCompleted()
{
	bMoveTriggerdThisFrame = false;
}

void AWWPlayerController::OnNormalLookActionTriggered(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void AWWPlayerController::OnJumpActionStarted()
{
	if (!CurrentParty[CurrentPlayerPawnIndex])
		return;

	CurrentParty[CurrentPlayerPawnIndex]->Jump();

}

void AWWPlayerController::OnJumpActionCompleted()
{
	if (!CurrentParty[CurrentPlayerPawnIndex])
		return;

	CurrentParty[CurrentPlayerPawnIndex]->StopJumping();
}

void AWWPlayerController::OnDashActionStarted()
{
	if (!CurrentParty[CurrentPlayerPawnIndex])
		return;

	CurrentParty[CurrentPlayerPawnIndex]->Dash();
}

void AWWPlayerController::OnNormalAttackActionStarted()
{
	if (!CurrentParty[CurrentPlayerPawnIndex])
		return;

	CurrentParty[CurrentPlayerPawnIndex]->NormalAttack();
}

void AWWPlayerController::OnSpecialAttackActionStarted()
{
	if (!CurrentParty[CurrentPlayerPawnIndex])
		return;

	CurrentParty[CurrentPlayerPawnIndex]->SpecialAttack();
}

void AWWPlayerController::OnEcoAttackActionStarted()
{
	if (!CurrentParty[CurrentPlayerPawnIndex])
		return;

	CurrentParty[CurrentPlayerPawnIndex]->EcoAttack();
}

void AWWPlayerController::OnUltimateAttackActionStarted()
{
	if (!CurrentParty[CurrentPlayerPawnIndex])
		return;

	CurrentParty[CurrentPlayerPawnIndex]->UltimateAttack();
}

void AWWPlayerController::OnChangePlayerPawnAction1Started()
{
	ChangePlayerPawn(0);
}

void AWWPlayerController::OnChangePlayerPawnAction2Started()
{
	ChangePlayerPawn(1);
}

void AWWPlayerController::OnChangePlayerPawnAction3Started()
{
	ChangePlayerPawn(2);
}

void AWWPlayerController::OpenMenu()
{
	if (!MenuWidget)
		return;

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;

	MenuWidget->OpenMenu();
}

void AWWPlayerController::CloseMenu()
{
	if (!MenuWidget)
		return;

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}
