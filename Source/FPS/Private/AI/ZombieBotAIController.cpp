// First Person Shooter, all rights reserved.

#include "AI/ZombieBotAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISense_Sight.h"

AZombieBotAIController::AZombieBotAIController() 
{
    PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
}

void AZombieBotAIController::BeginPlay()
{

}

void AZombieBotAIController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus) 
{

}