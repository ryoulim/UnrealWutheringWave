// Fill out your copyright notice in the Description page of Project Settings.


#include "WWRoleBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Net/UnrealNetwork.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameData/DataAsset/WWRoleDataAsset.h"
#include "Animation/WWRoleBaseAnimInstance.h"

// Sets default values
AWWRoleBase::AWWRoleBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/* 멀티플레이어: 서버에서 스폰된 Pawn이 클라이언트에 복제되도록 */
	bReplicates = true;
	SetReplicateMovement(true);

	/* 기본 설정값들 */
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	/* Capsule */
	GetCapsuleComponent()->InitCapsuleSize(18.f, 78.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	/* Movement */
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	/* 스켈레탈 메시를 숨기기 위한 설정 */
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -80.f), FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetVisibility(false);
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	
	/* 실제 렌더링될 메시 */
	RenderMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RenderMesh"));
	RenderMesh->SetupAttachment(GetMesh());
	RenderMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	RenderMesh->SetVisibility(true);
	RenderMesh->SetCollisionProfileName(TEXT("NoCollision"));

	/* 카메라 생성 */
	if (!CameraBoom)
	{
		CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
		CameraBoom->TargetArmLength = 400.0f;
		CameraBoom->SetupAttachment(RootComponent);
		CameraBoom->bUsePawnControlRotation = true;
	}

	if (!FollowCamera)
	{
		FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
		FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
		FollowCamera->bUsePawnControlRotation = false;
	}
}

void AWWRoleBase::OnField()
{
	SetActive(true);
}

void AWWRoleBase::OffField()
{
	SetActive(false);
}

void AWWRoleBase::CopyState(const ACharacter* Other)
{
	FVector   Pos = Other->GetActorLocation();
	FRotator Rot = Other->GetActorRotation();

	UCharacterMovementComponent* OtherMove = Other->GetCharacterMovement();
	UCharacterMovementComponent* Current = GetCharacterMovement();

	SetActorLocation(Pos, false,
		nullptr,
		ETeleportType::TeleportPhysics);

	SetActorRotation(Rot);

	//GetCharacterMovement()->FindFloor(GetActorLocation(), CurrentFloor, false);

	Current->Velocity = OtherMove->Velocity;
}

void AWWRoleBase::SetActive(bool bActive)
{
	SetActorHiddenInGame(!bActive);
	SetActorEnableCollision(bActive);
	SetActorTickEnabled(bActive);
}

void AWWRoleBase::SetSpeedRun()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void AWWRoleBase::SetSpeedSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AWWRoleBase::NormalMoveStart()
{
	if (HasAuthority())
	{
		MulticastNormalMoveStart();
	}
	else
	{
		ServerNormalMoveStart();
	}
}

void AWWRoleBase::NormalMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);
}

void AWWRoleBase::Dash()
{
	if (HasAuthority())
	{
		MulticastDash();
	}
	else
	{
		ServerDash();
	}
}

void AWWRoleBase::NormalAttack()
{
	if (HasAuthority())
	{
		MulticastNormalAttack();
	}
	else
	{
		ServerNormalAttack();
	}
}

void AWWRoleBase::SpecialAttack()
{
	if (HasAuthority())
	{
		MulticastSpecialAttack();
	}
	else
	{
		ServerSpecialAttack();
	}
}

void AWWRoleBase::EcoAttack()
{
	if (HasAuthority())
	{
		MulticastEcoAttack();
	}
	else
	{
		ServerEcoAttack();
	}
}

void AWWRoleBase::UltimateAttack()
{
	if (HasAuthority())
	{
		MulticastUltimateAttack();
	}
	else
	{
		ServerUltimateAttack();
	}
}

// Server RPC 구현
void AWWRoleBase::ServerDash_Implementation()
{
	MulticastDash();
}

bool AWWRoleBase::ServerDash_Validate()
{
	return true;
}

void AWWRoleBase::MulticastDash_Implementation()
{
	if (UWWRoleBaseAnimInstance* AnimInstatnce = Cast<UWWRoleBaseAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		AnimInstatnce->OnDashCall();
	}
}

void AWWRoleBase::ServerNormalAttack_Implementation()
{
	MulticastNormalAttack();
}

bool AWWRoleBase::ServerNormalAttack_Validate()
{
	return true;
}

void AWWRoleBase::MulticastNormalAttack_Implementation()
{
	if (UWWRoleBaseAnimInstance* AnimInstatnce = Cast<UWWRoleBaseAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		AnimInstatnce->OnNormalAttackCallCall();
	}
}

void AWWRoleBase::ServerSpecialAttack_Implementation()
{
	MulticastSpecialAttack();
}

bool AWWRoleBase::ServerSpecialAttack_Validate()
{
	return true;
}

void AWWRoleBase::MulticastSpecialAttack_Implementation()
{
	if (UWWRoleBaseAnimInstance* AnimInstatnce = Cast<UWWRoleBaseAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		AnimInstatnce->OnSpecialAttackCall();
	}
}

void AWWRoleBase::ServerEcoAttack_Implementation()
{
	MulticastEcoAttack();
}

bool AWWRoleBase::ServerEcoAttack_Validate()
{
	return true;
}

void AWWRoleBase::MulticastEcoAttack_Implementation()
{
	if (UWWRoleBaseAnimInstance* AnimInstatnce = Cast<UWWRoleBaseAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		AnimInstatnce->OnEcoAttackCall();
	}
}

void AWWRoleBase::ServerUltimateAttack_Implementation()
{
	MulticastUltimateAttack();
}

bool AWWRoleBase::ServerUltimateAttack_Validate()
{
	return true;
}

void AWWRoleBase::MulticastUltimateAttack_Implementation()
{
	if (UWWRoleBaseAnimInstance* AnimInstatnce = Cast<UWWRoleBaseAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		AnimInstatnce->OnUltimateAttackCall();
	}
}

void AWWRoleBase::ServerNormalMoveStart_Implementation()
{
	MulticastNormalMoveStart();
}

bool AWWRoleBase::ServerNormalMoveStart_Validate()
{
	return true;
}

void AWWRoleBase::MulticastNormalMoveStart_Implementation()
{
	if (UWWRoleBaseAnimInstance* AnimInstatnce = Cast<UWWRoleBaseAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		AnimInstatnce->OnMoveCall();
	}
}

void AWWRoleBase::SetUIMode(bool bInMode)
{
	bIsUIMode = bInMode;
}

void AWWRoleBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 멀티플레이어를 위한 Replication 설정
	// Character는 기본적으로 위치, 회전, 애니메이션 등이 자동으로 Replicated됨
	// 추가로 필요한 변수만 여기에 추가
	
	// UI 모드는 클라이언트에서만 사용하므로 Replication 불필요
	// 하지만 다른 플레이어가 보는 상태가 필요하면 추가 가능
}
