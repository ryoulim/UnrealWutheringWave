// Fill out your copyright notice in the Description page of Project Settings.


#include "WWRoleBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameData/DataAsset/WWRoleDataAsset.h"
#include "Animation/WWRoleBaseAnimInstance.h"

// Sets default values
AWWRoleBase::AWWRoleBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	/* 베이스 애님을 돌리기 위한 매쉬 */
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -80.f), FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetVisibility(false);
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	
	/* 실제 랜더링될 매쉬 */
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
	if (UWWRoleBaseAnimInstance* AnimInstatnce = Cast<UWWRoleBaseAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		AnimInstatnce->OnMoveCall();
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
	if (UWWRoleBaseAnimInstance* AnimInstatnce = Cast<UWWRoleBaseAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		AnimInstatnce->OnDashCall();
	}
}

void AWWRoleBase::NormalAttack()
{
	if (UWWRoleBaseAnimInstance* AnimInstatnce = Cast<UWWRoleBaseAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		AnimInstatnce->OnNormalAttackCallCall();
	}
}

void AWWRoleBase::SpecialAttack()
{
	if (UWWRoleBaseAnimInstance* AnimInstatnce = Cast<UWWRoleBaseAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		AnimInstatnce->OnSpecialAttackCall();
	}
}

void AWWRoleBase::EcoAttack()
{
	if (UWWRoleBaseAnimInstance* AnimInstatnce = Cast<UWWRoleBaseAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		AnimInstatnce->OnEcoAttackCall();
	}
}

void AWWRoleBase::UltimateAttack()
{
	if (UWWRoleBaseAnimInstance* AnimInstatnce = Cast<UWWRoleBaseAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		AnimInstatnce->OnUltimateAttackCall();
	}
}

void AWWRoleBase::SetUIMode(bool bInMode)
{
	bIsUIMode = bInMode;
}
