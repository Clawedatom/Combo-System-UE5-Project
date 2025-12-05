// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerMovementState.h"
#include "PlayerCharacter.h"
#include "PlayerSprintState.generated.h"




UCLASS()
class MGP_2425_API UPlayerSprintState : public UPlayerMovementState
{
	GENERATED_BODY()

public:
	UPlayerSprintState();

	virtual void OnStateEnter(APlayerCharacter* _player) override;
	virtual void OnStateUpdate(float DeltaSeconds) override;
	virtual void OnStateExit() override;
	virtual UPlayerBaseState* OnStateTransition() override;

};
