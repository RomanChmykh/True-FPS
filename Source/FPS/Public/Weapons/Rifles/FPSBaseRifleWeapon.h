// First Person Shooter, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/FPSBaseWeapon.h"
#include "FPSBaseRifleWeapon.generated.h"

/**
 *    Base rifle class
 */
UCLASS()
class FPS_API AFPSBaseRifleWeapon : public AFPSBaseWeapon
{
	GENERATED_BODY()
	
public:
    virtual void StartFire(AFPSCharacter* const Character);
    virtual void StopFire(AFPSCharacter* const Character);
};
