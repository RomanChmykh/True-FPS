// First Person Shooter, all rights reserved.

#include "AI/BaseZombieBot.h"

ABaseZombieBot::ABaseZombieBot()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseZombieBot::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseZombieBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseZombieBot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}