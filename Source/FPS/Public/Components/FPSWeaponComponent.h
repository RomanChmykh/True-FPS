// First Person Shooter, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapons/FPSBaseWeapon.h"
#include "FPSWeaponComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnWeaponTypeChanged, EWeaponType);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCurrentWeaponLHIKChanged, FTransform);

 /**
 * Weapon component for fps character
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UFPSWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFPSWeaponComponent();

    void PickUpWeapon(AFPSBaseWeapon* Weapon);

    void StartFire(AFPSCharacter* const Character);
    void StopFire(AFPSCharacter* const Character);

    void Realod(AFPSCharacter* const Character);

    void SetIsReload(bool const IsReload);

    FTransform CalculateCurrentWeaponLHIKTransform() const;

    FORCEINLINE AFPSBaseWeapon* GetCurrentWeapon() const { return CurrentWeapon; }

    FOnWeaponTypeChanged OnWeaponTypeChanged;
    FOnCurrentWeaponLHIKChanged OnCurrentWeaponLHIKChanged;

protected:
	virtual void BeginPlay() override;

	// Name of all weapon sockets
    UPROPERTY(EditDefaultsOnly, Category = "Sockets")
    FName PistolSocketName;

    UPROPERTY(EditDefaultsOnly, Category = "Sockets")
    FName RifleSocketName;

    UPROPERTY(EditDefaultsOnly, Category = "Sockets")
    FName ShotGunSocketName;

    UPROPERTY(EditDefaultsOnly, Category = "Sockets")
    FName GrenadeLauncherSocketName;

private:
    AFPSBaseWeapon* CurrentWeapon;

    bool bIsReload;
};