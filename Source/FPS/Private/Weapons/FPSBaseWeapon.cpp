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

FAnimationWeaponParameters::FAnimationWeaponParameters()
    : WeaponType(EWeaponType::WithoutWeapon), DeadZoneSensitivityPitch(0.0f), DeadZoneSensitivityYaw(0.0f), MinDeadZonePitch(0.0f),
      MaxDeadZonePitch(0.0f), MinDeadZoneYaw(0.0f), MaxDeadZoneYaw(0.0f)
{
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
    switch (AnimationWeaponParameters.WeaponType)
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
    SetFixClippingFOV(true);
}

void AFPSBaseWeapon::DetachFromCharacter(AFPSCharacter* const Character) 
{
    SetOwner(nullptr);

    DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

    Body->SetSimulatePhysics(true);
    Body->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionInteractionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SetFixClippingFOV(false);
}

void AFPSBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
    CollisionInteractionComponent->AttachToComponent(Body, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

    InitializeDynamicMaterials();
}

void AFPSBaseWeapon::InitializeDynamicMaterials()
{
    if (!Body || !Magazine) return;

    UMaterialInterface* BaseMatBody = Body->GetMaterial(0);
    UMaterialInterface* BaseMatMagazine = Magazine->GetMaterial(0);
    if (!BaseMatBody || !BaseMatMagazine) return;

    UMaterialInstanceDynamic* DynMatBody = UMaterialInstanceDynamic::Create(BaseMatBody, this);
    UMaterialInstanceDynamic* DynMatMagazine = UMaterialInstanceDynamic::Create(BaseMatMagazine, this);
    if (!DynMatBody || !DynMatMagazine) return;

    Body->SetMaterial(0, DynMatBody);
    Magazine->SetMaterial(0, DynMatMagazine);
}

void AFPSBaseWeapon::SetFixClippingFOV(bool bEnable)
{
    if (!Body || !Magazine) return;

    UMaterialInstanceDynamic* DynMatBody = Cast<UMaterialInstanceDynamic>(Body->GetMaterial(0));
    UMaterialInstanceDynamic* DynMatMagazine = Cast<UMaterialInstanceDynamic>(Magazine->GetMaterial(0));

    if (!DynMatBody || !DynMatMagazine) return;

    DynMatBody->SetScalarParameterValue(FName("Is Fix Clipping FOV"), bEnable ? 1.0f : 0.0f);
    DynMatMagazine->SetScalarParameterValue(FName("Is Fix Clipping FOV"), bEnable ? 1.0f : 0.0f);
}

UAnimMontage* AFPSBaseWeapon::GetRandomAnimMontage(const TArray<UAnimMontage*>& AnimMontages) const 
{
    if (AnimMontages.Num() == 0) return nullptr;

    int32 RandomIndex = FMath::RandRange(0, AnimMontages.Num() - 1);
    return AnimMontages[RandomIndex];
}

void AFPSBaseWeapon::StartFire(AFPSCharacter* const Character)
{

}

void AFPSBaseWeapon::StopFire(AFPSCharacter* const Character) 
{

}