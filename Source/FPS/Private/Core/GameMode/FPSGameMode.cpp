// First Person Shooter, all rights reserved.

#include "Core/GameMode/FPSGameMode.h"
#include "Character/FPSCharacter.h"
#include "Character/FPSPlayerController.h"

AFPSGameMode::AFPSGameMode()
{
    PrimaryActorTick.bCanEverTick = true;

    DefaultPawnClass = AFPSCharacter::StaticClass();
    PlayerControllerClass = AFPSPlayerController::StaticClass();
}