// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UPlayerBaseState.h"
#include "PlayerMovementState.h"
#include "PlayerWalkingState.generated.h"




UCLASS()
class MGP_2425_API UPlayerWalkingState : public UPlayerMovementState
{
	GENERATED_BODY()

public:
	UPlayerWalkingState();

	virtual void OnStateEnter(APlayerCharacter* _player) override;
	virtual void OnStateUpdate(float DeltaSeconds) override;
	virtual void OnStateExit() override;
	virtual UPlayerBaseState* OnStateTransition() override;
};
