// Fill out your copyright notice in the Description page of Project Settings.

#include "CloseWeaponNotify.h"
#include "PlayerCharacter.h"

#include "Kismet/GameplayStatics.h"


void UCloseWeaponNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{


	APlayerCharacter* player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if (player != nullptr)
	{
		player->CloseWeaponCollider();
	}
}