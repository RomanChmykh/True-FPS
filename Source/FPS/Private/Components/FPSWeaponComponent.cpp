// First Person Shooter, all rights reserved.

#include "Components/FPSWeaponComponent.h"
#include "Animations/Character/FPSBaseCharacterAnimInstance.h"

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

    OnAnimationWeaponParametersChanged.Broadcast(Weapon->GetWeaponType());
    OnCurrentWeaponLHIKChanged.Broadcast(CalculateCurrentWeaponLHIKTransform());
}

void UFPSWeaponComponent::StartFire(AFPSCharacter* const Character)
{
    if (!CurrentWeapon) return;

    CurrentWeapon->StartFire(Character);
}

void UFPSWeaponComponent::StopFire(AFPSCharacter* const Character)
{
    if (!CurrentWeapon) return;

    CurrentWeapon->StopFire(Character);
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

FTransform UFPSWeaponComponent::CalculateCurrentWeaponLHIKTransform() const
{
    AFPSCharacter* Character = Cast<AFPSCharacter>(GetOwner());
    if (!Character) return FTransform::Identity;

    USkeletalMeshComponent* CharacterMesh = Character->FindComponentByClass<USkeletalMeshComponent>();
    if (!CharacterMesh) return FTransform::Identity;

    if (!CurrentWeapon) return FTransform::Identity;
    USkeletalMeshComponent* WeaponMesh = CurrentWeapon->FindComponentByClass<USkeletalMeshComponent>();
    if (!WeaponMesh) return FTransform::Identity;

    FTransform SocketTransform = WeaponMesh->GetSocketTransform("LHIK", RTS_World);

    FVector OutPosition;
    FRotator OutRotation;

    CharacterMesh->TransformToBoneSpace("hand_r", SocketTransform.GetLocation(), SocketTransform.Rotator(), OutPosition, OutRotation);

    return FTransform(OutRotation, OutPosition);
}