// First Person Shooter, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Interfaces/\FPSInteractebleInterface.h"
#include "Character/FPSCharacter.h"
#include "FPSBaseWeapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    WithoutWeapon UMETA(DisplayName = "WithoutWeapon"),
    Pistol UMETA(DisplayName = "Pistol"),
    Rifle UMETA(DisplayName = "Rifle"),
    ShotGun UMETA(DisplayName = "ShotGun"),
    GrenadeLauncher UMETA(DisplayName = "GrenadeLauncher")
};

UCLASS()
class FPS_API AFPSBaseWeapon : public AActor, public IFPSInteractebleInterface
{
	GENERATED_BODY()
	
public:	
	AFPSBaseWeapon(const FObjectInitializer& ObjectInitializer);

	virtual void Interact(AFPSCharacter* const Character) override;
    
    void AttachToCharacter(AFPSCharacter* const Character);
    void DetachFromCharacter(AFPSCharacter* const Character);

    FORCEINLINE EWeaponType GetWeaponType() const { return WeaponType; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SkeletalMeshComponent")
    USkeletalMeshComponent* SkeletalMeshComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Collision Interaction")
    USphereComponent* CollisionInteractionComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Parameters")
    EWeaponType WeaponType;
};
