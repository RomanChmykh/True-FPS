// First Person Shooter, all rights reserved.

#include "Weapons/Rifles/FPSBaseRifleWeapon.h"

void AFPSBaseRifleWeapon::StartFire(AFPSCharacter* const Character)
{
    Super::StartFire(Character);

GetWorldTimerManager().SetTimer(
        FireTimerHandle,
        [this, Character]()
        {
            UAnimInstance* const CharacterAnimInstance = Character->GetMesh()->GetAnimInstance();
            if (!CharacterAnimInstance) return;

            UAnimInstance* const BodyAnimInstance = Body->GetAnimInstance();
            if (!BodyAnimInstance) return;

            const bool IsAiming = Character->GetIsAiming();

            if (IsAiming)
                CharacterAnimInstance->Montage_Play(GetRandomAnimMontage(CharacterAimShotAnimMontages));
            else
                CharacterAnimInstance->Montage_Play(GetRandomAnimMontage(CharacterShotAnimMontages));

            BodyAnimInstance->Montage_Play(GetRandomAnimMontage(BodyShotAnimMontages));

            if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("START FIRE FROM RIFLE!"));
        },
        0.2f, true);
}

void AFPSBaseRifleWeapon::StopFire(AFPSCharacter* const Character)
{
    Super::StartFire(Character);

    GetWorldTimerManager().ClearTimer(FireTimerHandle);
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("STOP FIRE FROM RIFLE!"));
}