// First Person Shooter, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Character/FPSCharacter.h"
#include "FPSInteractebleInterface.generated.h"

/*
// Class needed for unreal's reflection system
*/
UINTERFACE(MinimalAPI, Blueprintable)
class UFPSInteractebleInterface : public UInterface
{
    GENERATED_BODY()
};

/*
// Interacteble Interface
*/
class IFPSInteractebleInterface
{
    GENERATED_BODY()

public:
    virtual void Interact(AFPSCharacter* const Character) = 0;
};