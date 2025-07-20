// First Person Shooter, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AI/BaseZombieBot.h"
#include "MainZombieBot.generated.h"

/**
 *    main zombie class
 */
UCLASS()
class FPS_API AMainZombieBot : public ABaseZombieBot
{
	GENERATED_BODY()
	
public:
    AMainZombieBot();

protected:
    virtual void BeginPlay() override;

    // Body parts
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Body)
    USkeletalMeshComponent* LeftLeg;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Body)
    USkeletalMeshComponent* RightLeg;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Body)
    USkeletalMeshComponent* LeftArm;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Body)
    USkeletalMeshComponent* RightArm;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Body)
    USkeletalMeshComponent* Head;
};