// First Person Shooter, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSPlayerController.generated.h"

class UFPSInputComponent;
class UEnhancedInputLocalPlayerSubsystem;
class UInputMappingContext;
struct FInputActionValue;
/**
 *  Player Controller for FPS game
 */
UCLASS()
class FPS_API AFPSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    explicit AFPSPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
    
    /** Add input component */
    UPROPERTY(EditDefaultsOnly, Category = Input)
    UFPSInputComponent* FPSInputComponent;

protected:
    virtual void SetupInputComponent() override;
    virtual void BeginPlay() override;

    /** MappingContext */
    UPROPERTY(EditDefaultsOnly, Category = Input)
    UInputMappingContext* DefaultMappingContext;

private:
    void Move(const FInputActionValue& Value);

    void Look(const FInputActionValue& Value);

    void UpdatePitch(const FInputActionValue& Value);

    bool bInvertLookAxis;
};