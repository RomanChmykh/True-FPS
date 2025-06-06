// First Person Shooter, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Weapons/FPSBaseWeapon.h"
#include "FPSBaseCharacterAnimInstance.generated.h"

class AFPSCharacter;

    /**
 *    Base Anim Instance for Player Character
 */
UCLASS()
class FPS_API UFPSBaseCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
    UFPSBaseCharacterAnimInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    void UpdateAnimationPitch(const double InputPitch);
    void UpdateAnimationYaw(const double InputYaw);
    void UpdateAnimationRoll(const float InputRoll);
    void ResetAnimationRoll();

    void ActivateDeadZone(const FVector2D& Direction);
    void DeactivateDeadZone();

    void UpdateAnamationWeaponParameters(FAnimationWeaponParameters AnimationWeaponParameters);
    void UpdateCurrentWeaponLHIK(FTransform const LHIKTransform);

    void SetIsAiming(const bool IsAiming);
    void SetIsTurnRightLeft(const bool IsRight, const bool IsLeft);

protected:
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;
    virtual void NativeInitializeAnimation() override;

    float GetMovementDirection() const;
    void UpdateIsFalling();
    void UpdateSpeed();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Speed", meta = (ClampMin = "0.0", ClampMax = "5000.0", ToolTip = "Real speed for movement, also use like speed for animations"))
    float Speed;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
    FVector Velocity;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float Direction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float AnimationPitch;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float AnimationYaw;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float AnimationRoll;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    bool bIsFalling;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    bool bIsTurnRight;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    bool bIsTurnLeft;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aiming")
    bool bIsAiming;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aiming")
    float AnimationDeadZonePitch;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aiming")
    float AnimationDeadZoneYaw;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hand Sway")
    FTransform CurrentWeaponLHIKTransform;  // current weapon left hand IK transform

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Current Weapon Animation Parameters")
    AFPSCharacter* PlayerCharacter;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FAnimationWeaponParameters AnimationWeaponParameters;

    FTimerHandle ResetLeaningTimer; // timer for reset roll to default value after leaning
    FTimerHandle ResetDeadZoneTimer; // timer for reset deadzone pitch and yaw
};
