// First Person Shooter, all rights reserved.

#include "AI/Tasks/FPSMoveToRandomLocationBTT.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

UFPSMoveToRandomLocationBTT::UFPSMoveToRandomLocationBTT()
    : RadiusToPatroll(1000.f), CachedAIController(nullptr), MoveFinishedHandle(FDelegateHandle{}), CachedMoveRequestID(FAIRequestID{})
{
    NodeName = "Move To Random Location";
    bNotifyTick = false;
    bCreateNodeInstance = true;
}

EBTNodeResult::Type UFPSMoveToRandomLocationBTT::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    CachedAIController = OwnerComp.GetAIOwner();
    APawn* const AIPawn = CachedAIController ? CachedAIController->GetPawn() : nullptr;

    if (!AIPawn || !CachedAIController) 
        return EBTNodeResult::Failed;

    UNavigationSystemV1* const NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(AIPawn->GetWorld());
    if (!NavSystem)
        return EBTNodeResult::Failed;

    FVector Origin = AIPawn->GetActorLocation();
    FNavLocation RandomLocation;

    if (NavSystem->GetRandomReachablePointInRadius(Origin, 1000.f, RandomLocation))
    {
        FAIMoveRequest MoveRequest;
        MoveRequest.SetGoalLocation(RandomLocation.Location);
        MoveRequest.SetAcceptanceRadius(5.f);
        MoveRequest.SetNavigationFilter(nullptr);

        FNavPathSharedPtr NavPath;
        FPathFollowingRequestResult Result = CachedAIController->MoveTo(MoveRequest, &NavPath);

        if (Result.Code == EPathFollowingRequestResult::RequestSuccessful)
        {
            CachedMoveRequestID = Result.MoveId;

            MoveFinishedHandle = CachedAIController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(
                this, &UFPSMoveToRandomLocationBTT::OnMoveCompleted);

            return EBTNodeResult::InProgress;
        }
    }

    return EBTNodeResult::Failed;
}

void UFPSMoveToRandomLocationBTT::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    if (!RequestID.IsEquivalent(CachedMoveRequestID))
        return;

    if (!CachedAIController)
        return;

    UBehaviorTreeComponent* const BTComponent = Cast<UBehaviorTreeComponent>(CachedAIController->BrainComponent);

    if (BTComponent)
    {
        CachedAIController->GetPathFollowingComponent()->OnRequestFinished.Remove(MoveFinishedHandle);

        const EBTNodeResult::Type TaskResult = Result.IsSuccess() ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
        FinishLatentTask(*BTComponent, TaskResult);
    }
}