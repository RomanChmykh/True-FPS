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
    Super::BeginPlay();

    if (!BehaviorTreeAsset) return;
    RunBehaviorTree(BehaviorTreeAsset);

    if (!PerceptionComponent) return;
    PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AZombieBotAIController::OnHandleTargetPerceptionUpdated);

    SetGenericTeamId(FGenericTeamId(1));
}

void AZombieBotAIController::OnHandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus) 
{
    Blackboard->SetValueAsObject("BB_PlayerCharacter", Actor); // hard code perceprion key name for player character chasing by bot 

    Blackboard->SetValueAsBool("bSeePlayer", Stimulus.WasSuccessfullySensed()); // hard code perceprion key name if bot see player chacacter
}

ETeamAttitude::Type AZombieBotAIController::GetTeamAttitudeTowards(const AActor& Other) const 
{
    const IGenericTeamAgentInterface* const OtherTeamAgent = Cast<IGenericTeamAgentInterface>(&Other);
    if (!OtherTeamAgent) return ETeamAttitude::Neutral;

    if (OtherTeamAgent->GetGenericTeamId() == FGenericTeamId(0)) return ETeamAttitude::Hostile;

    return ETeamAttitude::Neutral;
}