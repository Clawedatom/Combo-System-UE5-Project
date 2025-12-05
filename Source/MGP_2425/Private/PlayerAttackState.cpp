// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackState.h"

#include "PlayerCharacter.h"

UPlayerAttackState::UPlayerAttackState()
{

}


void UPlayerAttackState::OnStateEnter(APlayerCharacter* _player)
{
    Super::OnStateEnter(_player);

    player->isAttacking = true;
    player->HandleLoseStam(player->attackStamCost);
    
}


void UPlayerAttackState::OnStateUpdate(float DeltaSeconds)
{
    Super::OnStateUpdate(DeltaSeconds);




}

void UPlayerAttackState::OnStateExit()
{
    Super::OnStateExit();

    player->isAttacking = false;
   
    player->comboAttacksDone = 0.0f;

    player->comboKnockbackPower = 0.0f;

}

UPlayerBaseState* UPlayerAttackState::OnStateTransition()
{
    Super::OnStateTransition();

    return this;
}

