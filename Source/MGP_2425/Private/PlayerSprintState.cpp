// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSprintState.h"

#include "PlayerCharacter.h"

UPlayerSprintState::UPlayerSprintState()
{

}

void UPlayerSprintState::OnStateEnter(APlayerCharacter* _player)
{
    Super::OnStateEnter(_player);

    player->SetMovementSpeed(player->sprintSpeed);
}

void UPlayerSprintState::OnStateUpdate(float DeltaSeconds)
{
    Super::OnStateUpdate(DeltaSeconds);

    player->HandleLoseStam(player->sprintStamCost);


}

void UPlayerSprintState::OnStateExit()
{
    Super::OnStateExit();
    
}

UPlayerBaseState* UPlayerSprintState::OnStateTransition()
{
    UPlayerBaseState* nextState = Super::OnStateTransition();
    
    return nextState;
}