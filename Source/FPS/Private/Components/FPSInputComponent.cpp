// First Person Shooter, all rights reserved.

#include "Components/FPSInputComponent.h"

UFPSInputComponent::UFPSInputComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
}

void UFPSInputComponent::BeginPlay()
{
	Super::BeginPlay();	
}