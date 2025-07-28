// First Person Shooter, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "FPSMoveToRandomLocationBTT.generated.h"

/**
 *	Task for bots to set and move to random location
 */
UCLASS()
class FPS_API UFPSMoveToRandomLocationBTT : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
    UFPSMoveToRandomLocationBTT();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);

    UPROPERTY(EditAnywhere, Category = Property)
    float RadiusToPatroll;

private:
    AAIController* CachedAIController;
    FDelegateHandle MoveFinishedHandle;
    FAIRequestID CachedMoveRequestID;
};