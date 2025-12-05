// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerIdleState.h"

#include "PlayerCharacter.h"

UPlayerIdleState::UPlayerIdleState()
{
}

void UPlayerIdleState::OnStateEnter(APlayerCharacter* _player)
{
    Super::OnStateEnter(_player);
    
}

void UPlayerIdleState::OnStateUpdate(float DeltaSeconds)
{
    Super::OnStateUpdate(DeltaSeconds);
    
}

void UPlayerIdleState::OnStateExit()
{
    Super::OnStateExit();
   
}

UPlayerBaseState* UPlayerIdleState::OnStateTransition()
{
    UPlayerBaseState* nextState = Super::OnStateTransition();


    if (player->GetMovementInput().Size() > 0.1f && player->isGrounded)
    {
        return player->walkState;
    }
    return nextState;
}