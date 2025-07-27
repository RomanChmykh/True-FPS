// First Person Shooter, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "ZombieBotAIController.generated.h"

UCLASS()
class FPS_API AZombieBotAIController : public AAIController
{
	GENERATED_BODY()
	
public:
    AZombieBotAIController();

    UFUNCTION()
    void OnHandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;
};