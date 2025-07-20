// First Person Shooter, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseZombieBot.generated.h"

UCLASS()
class FPS_API ABaseZombieBot : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseZombieBot();

	virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:	

};
