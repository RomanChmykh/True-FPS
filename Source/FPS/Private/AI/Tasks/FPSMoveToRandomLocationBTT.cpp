// First Person Shooter, all rights reserved.

#include "AI/Tasks/FPSMoveToRandomLocationBTT.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/MainZombie/MainZombieBot.h"

UFPSMoveToRandomLocationBTT::UFPSMoveToRandomLocationBTT()
{
    NodeName = "Move To Random Location";
}

EBTNodeResult::Type UFPSMoveToRandomLocationBTT::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AMainZombieBot* const Zombie = Cast<AMainZombieBot>(OwnerComp.GetAIOwner()->GetPawn());
    if (!Zombie) return EBTNodeResult::Failed;

    FVector const Origin = Zombie->GetActorLocation();
    UNavigationSystemV1* const NavSystem = UNavigationSystemV1::GetCurrent(Zombie->GetWorld());
    FNavLocation NavLocation;

    if (NavSystem && NavSystem->GetRandomPointInNavigableRadius(Origin, 75, NavLocation))
    {
        OwnerComp.GetAIOwner()->MoveToLocation(NavLocation.Location);
        return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
}