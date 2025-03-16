// First Person Shooter, all rights reserved.

#include "Weapons/Rifles/FPSBaseRifleWeapon.h"

void AFPSBaseRifleWeapon::StartFire(AFPSCharacter* const Character)
{
    Super::StartFire(Character);

    GetWorldTimerManager().SetTimer(
        FireTimerHandle, [this, Character]() { MakeShot(Character); }, 0.2f, true);

    MakeShot(Character);
}

void AFPSBaseRifleWeapon::StopFire(AFPSCharacter* const Character)
{
    Super::StartFire(Character);

    GetWorldTimerManager().ClearTimer(FireTimerHandle);
}
