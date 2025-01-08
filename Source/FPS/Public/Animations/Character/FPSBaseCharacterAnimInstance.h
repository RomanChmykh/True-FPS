// First Person Shooter, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FPSBaseCharacterAnimInstance.generated.h"

class AFPSCharacter;
/**
 * 
 */
UCLASS()
class FPS_API UFPSBaseCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
    UFPSBaseCharacterAnimInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    void UpdatePitch(double InputPitch);

protected:
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;
    virtual void NativeInitializeAnimation() override;

    float GetMovementDirection() const;
    void UpdateIsFalling();
    void UpdateSpeed();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Speed", meta = (ClampMin = "0.0", ClampMax = "5000.0", ToolTip = "Real speed for movement, also use like speed for animations"))
    float Speed;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float Direction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float Pitch;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    bool bIsFalling;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    AFPSCharacter* PlayerCharacter;
};
