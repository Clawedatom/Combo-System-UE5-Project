// Fill out your copyright notice in the Description page of Project Settings.


#include "UPlayerBaseState.h"
#include "PlayerCharacter.h"


UPlayerBaseState::UPlayerBaseState()
{
}



void UPlayerBaseState::OnStateEnter(APlayerCharacter* _player)
{
	player = _player;

	
}

void UPlayerBaseState::OnStateUpdate(float DeltaSeconds)
{

}

void UPlayerBaseState::OnStateExit()
{

}

UPlayerBaseState* UPlayerBaseState::OnStateTransition()
{
	if (!player->isGrounded)
	{
		return player->fallState;
	}
	return this;
}