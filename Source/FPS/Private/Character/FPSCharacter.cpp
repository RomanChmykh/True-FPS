// First Person Shooter, all rights reserved.

#include "Character/FPSCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/FPSWeaponComponent.h"
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
}

void AFPSCharacter::Look(const FVector2D& Direction) 
{
    if (!GetController()) return;

    AddControllerYawInput(Direction.X);
    AddControllerPitchInput(Direction.Y);
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

    AnimInstance->UpdateRoll(InputRoll);
}

void AFPSCharacter::StopLean() 
{
    USkeletalMeshComponent* const SkeletalMesh = GetMesh();
    if (!SkeletalMesh) return;

    UFPSBaseCharacterAnimInstance* AnimInstance = Cast<UFPSBaseCharacterAnimInstance>(SkeletalMesh->GetAnimInstance());
    if (!AnimInstance) return;

    AnimInstance->ResetRoll();
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

void AFPSCharacter::StartAim()
{
    USkeletalMeshComponent* const SkeletalMesh = GetMesh();
    if (!SkeletalMesh) return;

    UFPSBaseCharacterAnimInstance* AnimInstance = Cast<UFPSBaseCharacterAnimInstance>(SkeletalMesh->GetAnimInstance());
    if (!AnimInstance) return;

    AnimInstance->SetIsAiming(true);
}

void AFPSCharacter::StopAim() 
{
    USkeletalMeshComponent* const SkeletalMesh = GetMesh();
    if (!SkeletalMesh) return;

    UFPSBaseCharacterAnimInstance* AnimInstance = Cast<UFPSBaseCharacterAnimInstance>(SkeletalMesh->GetAnimInstance());
    if (!AnimInstance) return;

    AnimInstance->SetIsAiming(false);
}