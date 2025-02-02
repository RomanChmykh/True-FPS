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

    OnWeaponTypeChanged.Broadcast(Weapon->GetWeaponType());
}

void UFPSWeaponComponent::Realod(AFPSCharacter* const Character)
{
    if (!CurrentWeapon) return;

    if (bIsReload) return;

    bIsReload = true;

    CurrentWeapon->Realod(Character);
}

void UFPSWeaponComponent::SetIsReload(bool const IsReload) 
{
    bIsReload = IsReload;
}