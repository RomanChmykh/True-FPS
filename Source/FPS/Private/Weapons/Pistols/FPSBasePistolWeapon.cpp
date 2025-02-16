// First Person Shooter, all rights reserved.

#include "Weapons/Pistols/FPSBasePistolWeapon.h"

void AFPSBasePistolWeapon::StartFire(AFPSCharacter* const Character) 
{
    Super::StartFire(Character);

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("StartFire Pistol"));
    }
}

void AFPSBasePistolWeapon::StopFire(AFPSCharacter* const Character) 
{
    Super::StartFire(Character);

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("StopFire Pistol"));
    }
}