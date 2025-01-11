// First Person Shooter, all rights reserved.

#include "Character/FPSPlayerController.h"
#include "Character/FPSCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/FPSInputComponent.h"
#include "Animations/Character/FPSBaseCharacterAnimInstance.h"
#include "InputActionValue.h"
#include "FPSPlayerController.h"

AFPSPlayerController::AFPSPlayerController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer), bInvertLookAxis(false)
{
    FPSInputComponent = CreateDefaultSubobject<UFPSInputComponent>("FPSInputComponent");
}

void AFPSPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
}

void AFPSPlayerController::BeginPlay()
{
    Super::BeginPlay();

    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (Subsystem)
    {
        Subsystem->AddMappingContext(DefaultMappingContext, 0);
    }

    AFPSCharacter* const PlayerCharacter = GetPawn<AFPSCharacter>();
    UEnhancedInputComponent* const EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

    if (EnhancedInputComponent && PlayerCharacter)
    {
        /* Moving */
        EnhancedInputComponent->BindAction(FPSInputComponent->MoveAction, ETriggerEvent::Triggered, this, &AFPSPlayerController::Move);

        /* Looking */
        EnhancedInputComponent->BindAction(FPSInputComponent->LookAction, ETriggerEvent::Triggered, this, &AFPSPlayerController::Look);

        /* Pitch and Yaw*/
        EnhancedInputComponent->BindAction(FPSInputComponent->LookAction, ETriggerEvent::Triggered, this, &AFPSPlayerController::UpdatePitchAndYaw);

        /* Jumping*/
        EnhancedInputComponent->BindAction(FPSInputComponent->JumpAction, ETriggerEvent::Started, PlayerCharacter, &AFPSCharacter::StartJump);
        EnhancedInputComponent->BindAction(FPSInputComponent->JumpAction, ETriggerEvent::Completed, PlayerCharacter, &AFPSCharacter::StopJump);

        /* Leaning*/
        EnhancedInputComponent->BindAction(FPSInputComponent->LeanAction, ETriggerEvent::Triggered, this, &AFPSPlayerController::StartLean);
        EnhancedInputComponent->BindAction(FPSInputComponent->LeanAction, ETriggerEvent::Completed, this, &AFPSPlayerController::StopLean);

        /* Interact*/
        EnhancedInputComponent->BindAction(FPSInputComponent->InteractAction, ETriggerEvent::Started, PlayerCharacter, &AFPSCharacter::Interact);
    }
}

void AFPSPlayerController::Move(const FInputActionValue& Value) 
{
    AFPSCharacter* const PlayerCharacter = GetPawn<AFPSCharacter>();

    FVector2D MovementVector = Value.Get<FVector2D>();
    PlayerCharacter->Move(MovementVector);
}

void AFPSPlayerController::Look(const FInputActionValue& Value) 
{
    AFPSCharacter* const PlayerCharacter = GetPawn<AFPSCharacter>();
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    LookAxisVector *= bInvertLookAxis ? -1 : 1;
    PlayerCharacter->Look(LookAxisVector);
}

void AFPSPlayerController::UpdatePitchAndYaw(const FInputActionValue& Value)
{
    AFPSCharacter* const PlayerCharacter = GetPawn<AFPSCharacter>();
    if (!PlayerCharacter) return;

    USkeletalMeshComponent* const SkeletalMesh = PlayerCharacter->GetMesh();
    if (!SkeletalMesh) return;

    UFPSBaseCharacterAnimInstance* AnimInstance = Cast<UFPSBaseCharacterAnimInstance>(SkeletalMesh->GetAnimInstance());
    if (!AnimInstance) return;

    FVector2D LookAxisVector = Value.Get<FVector2D>();
    AnimInstance->UpdatePitch(LookAxisVector.Y * 0.5);
    AnimInstance->UpdateYaw(LookAxisVector.X);
}

void AFPSPlayerController::StartLean(const FInputActionValue& Value) 
{
    AFPSCharacter* const PlayerCharacter = GetPawn<AFPSCharacter>();
    if (!PlayerCharacter) return;

    PlayerCharacter->StartLean(Value.Get<float>());
}

void AFPSPlayerController::StopLean(const FInputActionValue& Value) 
{
    AFPSCharacter* const PlayerCharacter = GetPawn<AFPSCharacter>();
    if (!PlayerCharacter) return;

    PlayerCharacter->StopLean();
}