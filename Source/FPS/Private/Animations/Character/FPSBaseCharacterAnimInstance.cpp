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
    : Speed(0.0f), Direction(0.0f), Pitch(0.0f), bIsFalling(false)
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

void UFPSBaseCharacterAnimInstance::UpdatePitch(double InputPitch)
{
    float NewPitch = Pitch + InputPitch;
    Pitch = FMath::Clamp(NewPitch, -18.0f, 18.0f); // -18 and 18 its clamp for 5 bones that in summary clamp pitch eagle from -90 to 90
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

    Speed = PlayerCharacter->GetVelocity().Size();
}