// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerJumpState.h"

#include "PlayerCharacter.h"

UPlayerJumpState::UPlayerJumpState()
{
}


void UPlayerJumpState::OnStateEnter(APlayerCharacter* _player)
{
    Super::OnStateEnter(_player);

    //jump
    player->Jump();
    player->HandleLoseStam(player->jumpStamCost);
}

void UPlayerJumpState::OnStateUpdate(float DeltaSeconds)
{
    Super::OnStateUpdate(DeltaSeconds);




}

void UPlayerJumpState::OnStateExit()
{
    Super::OnStateExit();

    player->StopJumping();


}

UPlayerBaseState* UPlayerJumpState::OnStateTransition()
{
    UPlayerBaseState* nextState = Super::OnStateTransition();


    if (player->isGrounded)
    {
        return player->idleState;
    }
    return player->fallState;

    //if is grounded go to idle

    //if isnt grounded go to falling


}