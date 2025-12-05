// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UPlayerBaseState.generated.h"



class APlayerCharacter;

UCLASS(Blueprintable)
class MGP_2425_API UPlayerBaseState : public UObject
{
	GENERATED_BODY()
public:
	UPlayerBaseState();


	virtual void OnStateEnter(APlayerCharacter* _player);

	virtual void OnStateUpdate(float DeltaSeconds);

	virtual void OnStateExit();

	virtual UPlayerBaseState* OnStateTransition();


protected:
	UPROPERTY()
	APlayerCharacter* player;
};
