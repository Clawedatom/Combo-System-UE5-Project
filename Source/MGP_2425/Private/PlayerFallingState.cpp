// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFallingState.h"

#include "PlayerCharacter.h"

UPlayerFallingState::UPlayerFallingState()
{
    
}

void UPlayerFallingState::OnStateEnter(APlayerCharacter* _player)
{
    Super::OnStateEnter(_player);


}

void UPlayerFallingState::OnStateUpdate(float DeltaSeconds)
{
    Super::OnStateUpdate(DeltaSeconds);

    //fall


}

void UPlayerFallingState::OnStateExit()
{
    Super::OnStateExit();




}

UPlayerBaseState* UPlayerFallingState::OnStateTransition()
{
    UPlayerBaseState* nextState = Super::OnStateTransition();

    if (nextState == this)
    {
        if (player->isGrounded)
        {
            return player->idleState;
        }
    }
    //if is grounded go to idle

    //if isnt grounded go to falling

    return nextState;
}