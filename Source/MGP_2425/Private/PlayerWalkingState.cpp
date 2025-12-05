


#include "PlayerWalkingState.h"

#include "PlayerCharacter.h"

UPlayerWalkingState::UPlayerWalkingState()
{
    
}

void UPlayerWalkingState::OnStateEnter(APlayerCharacter* _player)
{
    Super::OnStateEnter(_player);

    player->SetMovementSpeed(player->walkSpeed);
}

void UPlayerWalkingState::OnStateUpdate(float DeltaSeconds)
{
    Super::OnStateUpdate(DeltaSeconds);




}

void UPlayerWalkingState::OnStateExit()
{
    Super::OnStateExit();
  
}

UPlayerBaseState* UPlayerWalkingState::OnStateTransition()
{
    UPlayerBaseState* nextState = Super::OnStateTransition();


    if (nextState != this)
    {
        return nextState;
    }
    return this;
}