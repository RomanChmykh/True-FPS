// First Person Shooter, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Interfaces/\FPSInteractebleInterface.h"
#include "Character/FPSCharacter.h"
#include "FPSBaseWeapon.generated.h"

class UAnimMontage;

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    WithoutWeapon UMETA(DisplayName = "WithoutWeapon"),
    Pistol UMETA(DisplayName = "Pistol"),
    Rifle UMETA(DisplayName = "Rifle"),
    ShotGun UMETA(DisplayName = "ShotGun"),
    GrenadeLauncher UMETA(DisplayName = "GrenadeLauncher")
};

USTRUCT(BlueprintType)
struct FAnimationWeaponParameters
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    EWeaponType WeaponType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float DeadZoneSensitivityPitch;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float DeadZoneSensitivityYaw;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float MinDeadZonePitch;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float MaxDeadZonePitch;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float MinDeadZoneYaw;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float MaxDeadZoneYaw;

    FAnimationWeaponParameters();
};

UCLASS()
class FPS_API AFPSBaseWeapon : public AActor, public IFPSInteractebleInterface
{
	GENERATED_BODY()
	
public:	
	AFPSBaseWeapon(const FObjectInitializer& ObjectInitializer);

	virtual void Interact(AFPSCharacter* const Character) override;

    virtual void StartFire(AFPSCharacter* const Character);
    virtual void StopFire(AFPSCharacter* const Character);

    void Realod(AFPSCharacter* const Character);
    
    void AttachToCharacter(AFPSCharacter* const Character);
    void DetachFromCharacter(AFPSCharacter* const Character);

    void MakeShot(AFPSCharacter* const Character);
    void PlayBodyAndMagazineAnimations(AFPSCharacter* const Character);

    FORCEINLINE FAnimationWeaponParameters GetWeaponType() const { return AnimationWeaponParameters; }
    FORCEINLINE USkeletalMeshComponent* GetMeshBody() const { return Body; }

protected:
	virtual void BeginPlay() override;

    void InitializeDynamicMaterials();
    void SetFixClippingFOV(bool bEnable);

    UAnimMontage* GetRandomAnimMontage(const TArray<UAnimMontage*>& AnimMontages) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SkeletalMesh")
    USkeletalMeshComponent* Body;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SkeletalMesh")
    USkeletalMeshComponent* Magazine;

    UPROPERTY(EditDefaultsOnly, Category = "Collision Interaction")
    USphereComponent* CollisionInteractionComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Parameters")
    FAnimationWeaponParameters AnimationWeaponParameters;

    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    TArray<UAnimMontage*> CharacterAimShotAnimMontages;

    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    TArray<UAnimMontage*> CharacterShotAnimMontages;

    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    TArray<UAnimMontage*> BodyShotAnimMontages;

    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    UAnimMontage* CharacterReloadAnimMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    UAnimMontage* MagazineReloadAnimMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Sockets")
    FName MagazineSocketName;

    FTimerHandle FireTimerHandle;
};