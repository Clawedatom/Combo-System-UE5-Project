// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UPlayerBaseState.h"
#include "PlayerIdleState.generated.h"



UCLASS(Blueprintable)
class MGP_2425_API UPlayerIdleState : public UPlayerBaseState
{
	GENERATED_BODY()

public:

	UPlayerIdleState();

	virtual void OnStateEnter(APlayerCharacter* _player) override;
	virtual void OnStateUpdate(float DeltaSeconds) override;
	virtual void OnStateExit() override;
	virtual UPlayerBaseState* OnStateTransition() override;

};
