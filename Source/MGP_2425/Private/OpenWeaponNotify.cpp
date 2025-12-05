// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenWeaponNotify.h"
#include "PlayerCharacter.h"

#include "Kismet/GameplayStatics.h"


void UOpenWeaponNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{


	APlayerCharacter* player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (player != nullptr)
	{
		
		player->OpenWeaponCollider();
	}
}