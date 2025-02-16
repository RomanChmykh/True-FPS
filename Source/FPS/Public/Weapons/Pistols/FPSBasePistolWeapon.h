// First Person Shooter, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/FPSBaseWeapon.h"
#include "FPSBasePistolWeapon.generated.h"

/**
 *   Base pistol class
 */
UCLASS()
class FPS_API AFPSBasePistolWeapon : public AFPSBaseWeapon
{
	GENERATED_BODY()
	
public:
    virtual void StartFire(AFPSCharacter* const Character);
    virtual void StopFire(AFPSCharacter* const Character);
};
