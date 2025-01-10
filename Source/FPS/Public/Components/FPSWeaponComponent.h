// First Person Shooter, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPSWeaponComponent.generated.h"


/**
 * Weapon component for fps character
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UFPSWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFPSWeaponComponent();

protected:
	
	virtual void BeginPlay() override;

};