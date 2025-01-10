// First Person Shooter, all rights reserved.

#include "Components/FPSWeaponComponent.h"

UFPSWeaponComponent::UFPSWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UFPSWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}