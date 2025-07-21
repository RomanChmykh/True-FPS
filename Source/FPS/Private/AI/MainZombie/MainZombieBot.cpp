// First Person Shooter, all rights reserved.

#include "AI/MainZombie/MainZombieBot.h"

AMainZombieBot::AMainZombieBot() 
{
    // Body setup
    LeftLeg = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftLeg"));
    LeftLeg->SetupAttachment(GetMesh());

    RightLeg = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightLeg"));
    RightLeg->SetupAttachment(GetMesh());

    LeftArm = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftArm"));
    LeftArm->SetupAttachment(GetMesh());

    RightArm = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightArm"));
    RightArm->SetupAttachment(GetMesh());

    Head = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Head"));
    Head->SetupAttachment(GetMesh());
}

void AMainZombieBot::BeginPlay() 
{
    Super::BeginPlay();
}

void AMainZombieBot::Move(const FVector2D& Direction) 
{

}

void AMainZombieBot::StopMove() 
{

}

void AMainZombieBot::StartAttack()
{

}

void AMainZombieBot::StopAttack() 
{

}