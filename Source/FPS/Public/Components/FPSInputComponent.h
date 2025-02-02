// First Person Shooter, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPSInputComponent.generated.h"

class UInputAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UFPSInputComponent final : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFPSInputComponent();

	UPROPERTY(EditDefaultsOnly, Category = Input)
    UInputAction* JumpAction;

    UPROPERTY(EditDefaultsOnly, Category = Input)
    UInputAction* MoveAction;

    UPROPERTY(EditDefaultsOnly, Category = Input)
    UInputAction* LookAction;

    UPROPERTY(EditDefaultsOnly, Category = Input)
    UInputAction* CrouchAction;

    UPROPERTY(EditDefaultsOnly, Category = Input)
    UInputAction* LeanAction;

    UPROPERTY(EditDefaultsOnly, Category = Input)
    UInputAction* InteractAction;

    UPROPERTY(EditDefaultsOnly, Category = Input)
    UInputAction* AimAction;

    UPROPERTY(EditDefaultsOnly, Category = Input)
    UInputAction* SprintAction;

    UPROPERTY(EditDefaultsOnly, Category = Input)
    UInputAction* RealodAction;

protected:
	virtual void BeginPlay() override;	
};