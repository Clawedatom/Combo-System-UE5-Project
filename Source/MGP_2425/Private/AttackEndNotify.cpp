// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackEndNotify.h"
#include "PlayerCharacter.h"

#include "Kismet/GameplayStatics.h"


void UAttackEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//change to idle state

	APlayerCharacter* player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (player != nullptr)
	{
		player->EndAttackMontage();

	}
}