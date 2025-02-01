// First Person Shooter, all rights reserved.

#include "Animations/Character/FPSBaseCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"       
#include "EnhancedInputSubsystems.h"      
#include "InputAction.h" 
#include "Character/FPSCharacter.h"
#include "Character/FPSPlayerController.h"
#include "Components/FPSInputComponent.h"


UFPSBaseCharacterAnimInstance::UFPSBaseCharacterAnimInstance(const FObjectInitializer& ObjectInitializer)
    : Speed(0.0f), Direction(0.0f), AnimationPitch(0.0f), AnimationYaw(0.0f), bIsFalling(false)
{
}

void UFPSBaseCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds) 
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    Direction = GetMovementDirection();
    UpdateIsFalling();
    UpdateSpeed();
}

void UFPSBaseCharacterAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    AFPSCharacter* const OwningActor = Cast<AFPSCharacter>(GetOwningActor());

    if (!OwningActor) return;

    PlayerCharacter = OwningActor;
}

float UFPSBaseCharacterAnimInstance::GetMovementDirection() const
{
    AActor* const Character = GetOwningActor();
    const FVector& VelocityVector = Character->GetVelocity();
    const FVector& ForwardVector = Character->GetActorForwardVector();
    if (VelocityVector.IsZero()) return 0.0f;

    const FVector& VelocityNormal = VelocityVector.GetSafeNormal();
    const float& AngleBetween = FMath::Acos(FVector::DotProduct(ForwardVector, VelocityNormal));
    const FVector& CrossProduct = FVector::CrossProduct(ForwardVector, VelocityNormal);
    const float& Degrees = FMath::RadiansToDegrees(AngleBetween);

    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void UFPSBaseCharacterAnimInstance::UpdateAnimationPitch(const double InputPitch)
{
    float NewPitch = AnimationPitch + InputPitch;
    AnimationPitch = FMath::Clamp(NewPitch, -18.0f, 18.0f);  // -18 and 18 its clamp for 5 bones that in summary clamp pitch eagle from -90 to 90
}

void UFPSBaseCharacterAnimInstance::UpdateAnimationYaw(const double InputYaw) 
{
    float NewYaw = (InputYaw * 0.6f) + AnimationYaw;
    AnimationYaw = FMath::Clamp(NewYaw, -10.0f, 10.0f);
}

void UFPSBaseCharacterAnimInstance::UpdateAnimationRoll(const float InputRoll) 
{
    UWorld* World = GetOwningActor()->GetWorld();  
    if (!World) return;

    if (World->GetTimerManager().IsTimerActive(ResetLeaningTimer))
    {
        World->GetTimerManager().ClearTimer(ResetLeaningTimer);
    }

    const float TargetRoll = FMath::GetMappedRangeValueClamped(FVector2D(-1.0f, 1.0f), FVector2D(-10.0f, 10.0f), InputRoll);

    AnimationRoll = FMath::FInterpTo(AnimationRoll, TargetRoll, World->GetDeltaSeconds(), 10.0f);
}

void UFPSBaseCharacterAnimInstance::ResetAnimationRoll() 
{
    if (UWorld* World = GetOwningActor()->GetWorld())
    {
        World->GetTimerManager().SetTimer(
            ResetLeaningTimer,
            [this, World]()
            {
                AnimationRoll = FMath::FInterpTo(AnimationRoll, 0.0f, World->GetDeltaSeconds(), 10.0f);

                // ???? Roll ????????? ???????? ?? 0, ????????? ??????
                if (FMath::IsNearlyZero(AnimationRoll, 0.01f))
                {
                    AnimationRoll = 0.0f;
                    World->GetTimerManager().ClearTimer(ResetLeaningTimer);
                }
            },
            0.01f, true);
    }
}

void UFPSBaseCharacterAnimInstance::UpdateWeaponType(EWeaponType NewWeaponType)
{
    WeaponType = NewWeaponType;
}

void UFPSBaseCharacterAnimInstance::SetIsAiming(const bool IsAiming)
{
    bIsAiming = IsAiming;
}

void UFPSBaseCharacterAnimInstance::SetIsTurnRightLeft(const bool IsRight, const bool IsLeft)
{
    bIsTurnRight = IsRight;
    bIsTurnLeft = IsLeft;
}

void UFPSBaseCharacterAnimInstance::UpdateIsFalling()
{
    if (!PlayerCharacter) return;

    UCharacterMovementComponent* const PlayerMovementComponent = PlayerCharacter->GetCharacterMovement();
    if (!PlayerMovementComponent) return;

    bIsFalling = PlayerMovementComponent->IsFalling();
}

void UFPSBaseCharacterAnimInstance::UpdateSpeed()
{
    if (!PlayerCharacter) return;

    Velocity = PlayerCharacter->GetVelocity();
    Speed = Velocity.Size2D();
}