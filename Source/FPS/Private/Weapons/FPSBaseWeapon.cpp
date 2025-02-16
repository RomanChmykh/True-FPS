// First Person Shooter, all rights reserved.

#include "Weapons/FPSBaseWeapon.h"
#include "Components/FPSWeaponComponent.h"

AFPSBaseWeapon::AFPSBaseWeapon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), MagazineSocketName("mag")
{
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
    SetRootComponent(Body);
    Body->SetSimulatePhysics(true);
    Body->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    Body->SetCollisionResponseToAllChannels(ECR_Block);

    Magazine = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Magazine"));
    Magazine->SetupAttachment(Body, MagazineSocketName);
    Magazine->SetSimulatePhysics(false);
    Magazine->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    CollisionInteractionComponent = CreateDefaultSubobject<USphereComponent>("Collision Interaction");
    CollisionInteractionComponent->SetupAttachment(Body);
    CollisionInteractionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionInteractionComponent->SetSimulatePhysics(false);

    float CollisionSphereRadius = 100.0f;
    CollisionInteractionComponent->SetSphereRadius(CollisionSphereRadius);
}

void AFPSBaseWeapon::Interact(AFPSCharacter* const Character) 
{

}

void AFPSBaseWeapon::Realod(AFPSCharacter* const Character) 
{
    UAnimInstance* const ChatacterAnimInstance = Character->GetMesh()->GetAnimInstance();
    if (!ChatacterAnimInstance) return;

    UAnimInstance* const MagazineAnimInstance = Magazine->GetAnimInstance();
    if (!MagazineAnimInstance) return;

    ChatacterAnimInstance->Montage_Play(CharacterReloadAnimMontage);
    MagazineAnimInstance->Montage_Play(MagazineReloadAnimMontage);

    FOnMontageEnded EndDelegate;
    EndDelegate.BindLambda(
        [Character](UAnimMontage* Montage, bool bInterrupted)
        {
            if (!bInterrupted && Character)
            {
                UFPSWeaponComponent* WeaponComponent = Character->FindComponentByClass<UFPSWeaponComponent>();

                if (WeaponComponent) WeaponComponent->SetIsReload(false);
            }
        });

    ChatacterAnimInstance->Montage_SetEndDelegate(EndDelegate, CharacterReloadAnimMontage);
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

    Body->SetSimulatePhysics(false);
    Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    CollisionInteractionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    AttachToComponent(CharacterMeshComponent, AttachmentRules, SocketName);
}

void AFPSBaseWeapon::DetachFromCharacter(AFPSCharacter* const Character) 
{
    SetOwner(nullptr);

    DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

    Body->SetSimulatePhysics(true);
    Body->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionInteractionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AFPSBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
    CollisionInteractionComponent->AttachToComponent(Body, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void AFPSBaseWeapon::StartFire(AFPSCharacter* const Character)
{

}

void AFPSBaseWeapon::StopFire(AFPSCharacter* const Character) 
{

}