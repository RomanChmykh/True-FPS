// First Person Shooter, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;
class UFPSWeaponComponent;

UCLASS()
class FPS_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
    AFPSCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	#pragma region Moving

	UFUNCTION(BlueprintCallable, Category = "Movement", meta = (ToolTip = "Moves the character in the specified direction. Direction should be a normalized vector."))
    void Move(const FVector2D& Direction);

    void Look(const FVector2D& Direction);

    void StartCrouch();
    void StopCrouch();

    void StartJump();
    void StopJump();

    void StartLean(const float InputRoll);
    void StopLean();

	#pragma endregion

    void Interact();

    FORCEINLINE UFPSWeaponComponent* GetWeaponComponent() const { return FPSWeaponComponent; }

protected:
	virtual void BeginPlay() override;

    /* FPS camera */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera)
    UCameraComponent* FPCamera;

    UPROPERTY(EditDefaultsOnly, Category = Camera)
    FName FPCameraSocketName;

    //Body
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Body)
    USkeletalMeshComponent* Feet;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Body)
    USkeletalMeshComponent* Legs;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Body)
    USkeletalMeshComponent* Torso;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Body)
    USkeletalMeshComponent* Face;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UFPSWeaponComponent* FPSWeaponComponent;
};