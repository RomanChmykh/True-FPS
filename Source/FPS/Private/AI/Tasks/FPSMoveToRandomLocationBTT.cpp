// First Person Shooter, all rights reserved.

#include "AI/Tasks/FPSMoveToRandomLocationBTT.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

UFPSMoveToRandomLocationBTT::UFPSMoveToRandomLocationBTT()
{
    NodeName = "Move To Random Location";
    bNotifyTick = false;
    bCreateNodeInstance = true;
}

EBTNodeResult::Type UFPSMoveToRandomLocationBTT::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    CachedAIController = OwnerComp.GetAIOwner();
    if (!CachedAIController)
    {
        UE_LOG(LogTemp, Warning, TEXT("No AIController"));
        return EBTNodeResult::Failed;
    }

    UPathFollowingComponent* PathComp = CachedAIController->GetPathFollowingComponent();
    if (!PathComp)
    {
        UE_LOG(LogTemp, Warning, TEXT("No PathFollowingComponent"));
        return EBTNodeResult::Failed;
    }

    MoveFinishedHandle = PathComp->OnRequestFinished.AddUObject(this, &UFPSMoveToRandomLocationBTT::OnMoveCompleted);

    if (!FindRandomLocationAndMove(OwnerComp))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to find random location"));
        PathComp->OnRequestFinished.Remove(MoveFinishedHandle);
        return EBTNodeResult::Failed;
    }

    return EBTNodeResult::InProgress;
}

bool UFPSMoveToRandomLocationBTT::FindRandomLocationAndMove(UBehaviorTreeComponent& OwnerComp)
{
    if (!CachedAIController)
    {
        UE_LOG(LogTemp, Warning, TEXT("No AIController"));
        return false;
    }

    APawn* Pawn = CachedAIController->GetPawn();
    if (!Pawn)
    {
        UE_LOG(LogTemp, Warning, TEXT("No Pawn"));
        return false;
    }

    UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
    if (!NavSys)
    {
        UE_LOG(LogTemp, Warning, TEXT("No NavigationSystem"));
        return false;
    }

    FNavLocation RandomLocation;
    const float Radius = 1000.f;

    if (!NavSys->GetRandomPointInNavigableRadius(Pawn->GetActorLocation(), Radius, RandomLocation))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to find random point"));
        return false;
    }

    MoveRequestID = CachedAIController->MoveToLocation(RandomLocation.Location);
    if (!MoveRequestID.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid MoveRequestID"));
        return false;
    }

    UE_LOG(LogTemp, Log, TEXT("Moving to location: %s"), *RandomLocation.Location.ToString());

    return true;
}

void UFPSMoveToRandomLocationBTT::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    UE_LOG(LogTemp, Log, TEXT("OnMoveCompleted called with Result: %d"), (int)Result.Code);

    if (UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(CachedAIController->BrainComponent))
    {
        CachedAIController->GetPathFollowingComponent()->OnRequestFinished.Remove(MoveFinishedHandle);

        if (Result.IsSuccess())
        {
            FinishLatentTask(*BTComp, EBTNodeResult::Succeeded);
        }
        else
        {
            FinishLatentTask(*BTComp, EBTNodeResult::Failed);
        }
    }
}

void UFPSMoveToRandomLocationBTT::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
    Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

    UE_LOG(LogTemp, Log, TEXT("Task finished with result: %s"), *UEnum::GetValueAsString(TaskResult));
}