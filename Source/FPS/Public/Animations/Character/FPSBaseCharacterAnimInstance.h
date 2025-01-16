// First Person Shooter, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FPSBaseCharacterAnimInstance.generated.h"

class AFPSCharacter;
enum class EWeaponType : uint8;
    /**
 * 
 */
UCLASS()
class FPS_API UFPSBaseCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
    UFPSBaseCharacterAnimInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    void UpdatePitch(const double InputPitch);
    void UpdateYaw(const double InputYaw);
    void UpdateRoll(const float InputRoll);
    void ResetRoll();

    void UpdateWeaponType(EWeaponType NewWeaponType);

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
    float Pitch;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float Yaw;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float Roll;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    bool bIsFalling;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    AFPSCharacter* PlayerCharacter;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    EWeaponType WeaponType;

    FTimerHandle ResetLeaningTimer; // timer for reset roll to default value after leaning
};
