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

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};