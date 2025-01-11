// First Person Shooter, all rights reserved.

#include "Weapons/FPSBaseWeapon.h"

AFPSBaseWeapon::AFPSBaseWeapon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
    SkeletalMeshComponent->SetupAttachment(RootComponent);
    SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    SkeletalMeshComponent->SetCollisionResponseToAllChannels(ECR_Block);
    SkeletalMeshComponent->SetSimulatePhysics(true);

    CollisionInteractionComponent = CreateDefaultSubobject<USphereComponent>("Collision Interaction");
    CollisionInteractionComponent->SetupAttachment(SkeletalMeshComponent);
    CollisionInteractionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    float CollisionSphereRadius = 100.0f;
    CollisionInteractionComponent->SetSphereRadius(CollisionSphereRadius);
}

void AFPSBaseWeapon::Interact(AFPSCharacter* const Character) 
{

}

void AFPSBaseWeapon::AttachToCharacter(AFPSCharacter* const Character)
{
    SetOwner(Character);

    USkeletalMeshComponent* CharacterMeshComponent = Character->FindComponentByClass<USkeletalMeshComponent>();
    if (!CharacterMeshComponent) return;

    FName SocketName;
    switch (WeaponType)
    {
        case EWeaponType::Pistol: SocketName = FName("Pistol_Socket"); break;
        case EWeaponType::Rifle: SocketName = FName("Rifle_Socket"); break;
        case EWeaponType::ShotGun: SocketName = FName("ShotGun_Socket"); break;
        case EWeaponType::GrenadeLauncher: SocketName = FName("GrenadeLauncher_Socket"); break;
        default: SocketName = FName("DefaultSocket"); break;
    }

    SkeletalMeshComponent->SetSimulatePhysics(false);
    SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    CollisionInteractionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    AttachToComponent(CharacterMeshComponent, AttachmentRules, SocketName);
}

void AFPSBaseWeapon::DetachFromCharacter(AFPSCharacter* const Character) 
{
    SetOwner(nullptr);

    DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

    SkeletalMeshComponent->SetSimulatePhysics(true);
    SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionInteractionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AFPSBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}