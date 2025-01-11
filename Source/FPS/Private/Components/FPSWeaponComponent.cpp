// First Person Shooter, all rights reserved.

#include "Components/FPSWeaponComponent.h"

UFPSWeaponComponent::UFPSWeaponComponent()
    : PistolSocketName("Pistol_Socket"), RifleSocketName("Rifle_Socket"), ShotGunSocketName("ShotGun_Socket"), 
	  GrenadeLauncherSocketName("GrenadeLauncher_Socket")
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFPSWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UFPSWeaponComponent::PickUpWeapon(AFPSBaseWeapon* Weapon) 
{
    AFPSCharacter* const Character = Cast<AFPSCharacter>(GetOwner());
    if (!Character) return;

    if (CurrentWeapon)
    {
        CurrentWeapon->DetachFromCharacter(Character);

        Weapon->AttachToCharacter(Character);
        CurrentWeapon = Weapon;
    }
    else
    {
        Weapon->AttachToCharacter(Character);
        CurrentWeapon = Weapon;
    }
}