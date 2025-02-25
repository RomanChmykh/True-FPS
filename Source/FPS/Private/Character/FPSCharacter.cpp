// First Person Shooter, all rights reserved.

#include "Character/FPSCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/FPSWeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animations/Character/FPSBaseCharacterAnimInstance.h"
#include "Interfaces/FPSInteractebleInterface.h"

AFPSCharacter::AFPSCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), FPCameraSocketName(TEXT("spine_05"))
{
	PrimaryActorTick.bCanEverTick = true;

    //Camera
    FPCamera = CreateDefaultSubobject<UCameraComponent>("FPCamera");
    FPCamera->SetupAttachment(GetMesh(), FPCameraSocketName);
    FPCamera->bUsePawnControlRotation = true;

    //Body
    Feet = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Feet"));
    Feet->SetupAttachment(GetMesh());

    Legs = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Legs"));
    Legs->SetupAttachment(GetMesh());

    Torso = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Torso"));
    Torso->SetupAttachment(GetMesh());

    //Face
    Face = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Face"));
    Face->SetupAttachment(GetMesh());

    FPSWeaponComponent = CreateDefaultSubobject<UFPSWeaponComponent>("Weapon Component");
}

void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

    USkeletalMeshComponent* SkeletalMesh = GetMesh();
    if (!SkeletalMesh) return;

    UFPSBaseCharacterAnimInstance* AnimInstance = Cast<UFPSBaseCharacterAnimInstance>(SkeletalMesh->GetAnimInstance());
    if (!AnimInstance) return;

    FPSWeaponComponent->OnWeaponTypeChanged.AddUObject(AnimInstance, &UFPSBaseCharacterAnimInstance::UpdateWeaponType);
    FPSWeaponComponent->OnCurrentWeaponLHIKChanged.AddUObject(AnimInstance, &UFPSBaseCharacterAnimInstance::UpdateCurrentWeaponLHIK);
}

void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFPSCharacter::Move(const FVector2D& Direction) 
{
    if (GetController())
    {
        /* fint out with way is forward */
        const FRotator Rotation = GetController()->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        /* get forward vector */
        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        /* get right vector */
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        /* add movement */
        AddMovementInput(ForwardDirection, Direction.Y);
        AddMovementInput(RightDirection, Direction.X);
    }

    bIsWalk = true;
}

void AFPSCharacter::StopMove()
{
    bIsWalk = false;
}

void AFPSCharacter::Look(const FVector2D& Direction) 
{
    if (!GetController()) return;

    AddControllerYawInput(Direction.X);
    AddControllerPitchInput(Direction.Y);
}

void AFPSCharacter::StopLook()
{
    CalculateCharacterTurnRightLeft(FVector2D(0.0f, 0.0f));
}

void AFPSCharacter::StartCrouch() {}

void AFPSCharacter::StopCrouch() {}

void AFPSCharacter::StartJump() 
{
    Jump();
}

void AFPSCharacter::StopJump()
{
    StopJumping();
}

void AFPSCharacter::StartLean(const float InputRoll) 
{
    USkeletalMeshComponent* const SkeletalMesh = GetMesh();
    if (!SkeletalMesh) return;

    UFPSBaseCharacterAnimInstance* AnimInstance = Cast<UFPSBaseCharacterAnimInstance>(SkeletalMesh->GetAnimInstance());
    if (!AnimInstance) return;

    AnimInstance->UpdateAnimationRoll(InputRoll);
}

void AFPSCharacter::StopLean() 
{
    USkeletalMeshComponent* const SkeletalMesh = GetMesh();
    if (!SkeletalMesh) return;

    UFPSBaseCharacterAnimInstance* AnimInstance = Cast<UFPSBaseCharacterAnimInstance>(SkeletalMesh->GetAnimInstance());
    if (!AnimInstance) return;

    AnimInstance->ResetAnimationRoll();
}

void AFPSCharacter::StartSprint()
{
    if (!bIsWalk) return;

    if (bIsAiming) StopAim();

    UCharacterMovementComponent* const MovementComp = GetCharacterMovement();
    if (!MovementComp) return;

    MovementComp->MaxWalkSpeed = 600.0f;
    bIsSprint = true;
}

void AFPSCharacter::StopSprint()
{
    UCharacterMovementComponent* const MovementComp = GetCharacterMovement();
    if (!MovementComp) return;

    MovementComp->MaxWalkSpeed = 400.0f;
    bIsSprint = false;
}

void AFPSCharacter::Interact()
{
    UCapsuleComponent* Capsule = GetCapsuleComponent();
    if (!Capsule) return;

    TArray<AActor*> OverlappingActors;
    Capsule->GetOverlappingActors(OverlappingActors);

    for (AActor* Actor : OverlappingActors)
    {
        if (!Actor) continue;

        if (Actor->Implements<UFPSInteractebleInterface>())
        {
            AFPSBaseWeapon* Weapon = Cast<AFPSBaseWeapon>(Actor);
            if (Weapon)
            {
                if (FPSWeaponComponent)
                {
                    FPSWeaponComponent->PickUpWeapon(Weapon);
                }
            }
            else
            {
                IFPSInteractebleInterface* InteractObj = Cast<IFPSInteractebleInterface>(Actor);
                if (InteractObj)
                {
                    InteractObj->Interact(this);
                }
            }

            break;
        }
    }
}

void AFPSCharacter::StartFire()
{
    if (!FPSWeaponComponent) return;

    FPSWeaponComponent->StartFire(this);
}

void AFPSCharacter::StopFire() 
{
    if (!FPSWeaponComponent) return;

    FPSWeaponComponent->StopFire(this);
}

void AFPSCharacter::StartAim()
{
    if (bIsSprint) StopSprint();

    USkeletalMeshComponent* const SkeletalMesh = GetMesh();
    if (!SkeletalMesh) return;

    UFPSBaseCharacterAnimInstance* AnimInstance = Cast<UFPSBaseCharacterAnimInstance>(SkeletalMesh->GetAnimInstance());
    if (!AnimInstance) return;

    bIsAiming = true;
    bIsDeadZoneEnable = true;

    AnimInstance->SetIsAiming(bIsAiming);
}

void AFPSCharacter::StopAim() 
{
    USkeletalMeshComponent* const SkeletalMesh = GetMesh();
    if (!SkeletalMesh) return;

    UFPSBaseCharacterAnimInstance* AnimInstance = Cast<UFPSBaseCharacterAnimInstance>(SkeletalMesh->GetAnimInstance());
    if (!AnimInstance) return;

    bIsAiming = false;
    bIsDeadZoneEnable = false;

    AnimInstance->SetIsAiming(bIsAiming);
    AnimInstance->DeactivateDeadZone();
}

void AFPSCharacter::Realod()
{
    if (!FPSWeaponComponent) return;

    FPSWeaponComponent->Realod(this);
}

void AFPSCharacter::UpdateAnimationPitchAndYaw(const FVector2D& Value) 
{
    USkeletalMeshComponent* const SkeletalMesh = GetMesh();
    if (!SkeletalMesh) return;

    UFPSBaseCharacterAnimInstance* AnimInstance = Cast<UFPSBaseCharacterAnimInstance>(SkeletalMesh->GetAnimInstance());
    if (!AnimInstance) return;

    AnimInstance->UpdateAnimationPitch(Value.Y * 0.5);
    AnimInstance->UpdateAnimationYaw(Value.X);
}

void AFPSCharacter::CalculateCharacterTurnRightLeft(const FVector2D& Value) 
{
    USkeletalMeshComponent* const SkeletalMesh = GetMesh();
    if (!SkeletalMesh) return;

    UFPSBaseCharacterAnimInstance* AnimInstance = Cast<UFPSBaseCharacterAnimInstance>(SkeletalMesh->GetAnimInstance());
    if (!AnimInstance) return;

    float TurnAxis = Value.X;
    float const Speed = GetVelocity().Size();

    if (Speed > 0.01f)
    {
        AnimInstance->SetIsTurnRightLeft(false, false);
        return; 
    }

    if (TurnAxis > 0.1f) AnimInstance->SetIsTurnRightLeft(true, false);
    else if (TurnAxis < -0.1f)
        AnimInstance->SetIsTurnRightLeft(false, true);
    else
        AnimInstance->SetIsTurnRightLeft(false, false);
}

void AFPSCharacter::ActivateDeadZone(const FVector2D& Value)
{
    if (!bIsDeadZoneEnable) return;

    USkeletalMeshComponent* const SkeletalMesh = GetMesh();
    if (!SkeletalMesh) return;

    UFPSBaseCharacterAnimInstance* AnimInstance = Cast<UFPSBaseCharacterAnimInstance>(SkeletalMesh->GetAnimInstance());
    if (!AnimInstance) return;

    AnimInstance->ActivateDeadZone(Value);
}

void AFPSCharacter::DeactivateDeadZone() 
{
    USkeletalMeshComponent* const SkeletalMesh = GetMesh();
    if (!SkeletalMesh) return;

    UFPSBaseCharacterAnimInstance* AnimInstance = Cast<UFPSBaseCharacterAnimInstance>(SkeletalMesh->GetAnimInstance());
    if (!AnimInstance) return;

    AnimInstance->DeactivateDeadZone();
}