// First Person Shooter, all rights reserved.

#include "Weapons/Pistols/FPSBasePistolWeapon.h"
#include "Components/FPSWeaponComponent.h"

void AFPSBasePistolWeapon::StartFire(AFPSCharacter* const Character) 
{
    Super::StartFire(Character);

    UAnimInstance* const ChatacterAnimInstance = Character->GetMesh()->GetAnimInstance();
    if (!ChatacterAnimInstance) return;

    UAnimInstance* const BodyAnimInstance = Body->GetAnimInstance();
    if (!BodyAnimInstance) return;

    const bool IsAiming = Character->GetIsAiming();

    if (IsAiming) 
        ChatacterAnimInstance->Montage_Play(GetRandomAnimMontage(CharacterAimShotAnimMontages));
    else 
        ChatacterAnimInstance->Montage_Play(GetRandomAnimMontage(CharacterShotAnimMontages));
    
    BodyAnimInstance->Montage_Play(GetRandomAnimMontage(BodyShotAnimMontages));
}

void AFPSBasePistolWeapon::StopFire(AFPSCharacter* const Character) 
{
    Super::StartFire(Character);


}