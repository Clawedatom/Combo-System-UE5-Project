// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UPlayerBaseState.h"
#include "PlayerFallingState.generated.h"


UCLASS()
class MGP_2425_API UPlayerFallingState : public UPlayerBaseState
{
	GENERATED_BODY()

public:
	UPlayerFallingState();


	virtual void OnStateEnter(APlayerCharacter* _player);

	virtual void OnStateUpdate(float DeltaSeconds);

	virtual void OnStateExit();

	virtual UPlayerBaseState* OnStateTransition();

};
