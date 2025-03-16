// First Person Shooter, all rights reserved.

#include "Weapons/Pistols/FPSBasePistolWeapon.h"
#include "Components/FPSWeaponComponent.h"

void AFPSBasePistolWeapon::StartFire(AFPSCharacter* const Character)
{
    Super::StartFire(Character);

    MakeShot(Character);
}

void AFPSBasePistolWeapon::StopFire(AFPSCharacter* const Character)
{
    Super::StartFire(Character);
}