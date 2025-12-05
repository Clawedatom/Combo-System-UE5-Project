// Fill out your copyright notice in the Description page of Project Settings.
#include "ComboCheckNotify.h"
#include "PlayerCharacter.h"

#include "Kismet/GameplayStatics.h"

void UComboCheckNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

	APlayerCharacter* player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	// if player->wants to combo

	if (player != nullptr)
	{
		if (player->comboFlag)
		{
			player->comboFlag = false;
		}
		else if (!player->comboFlag)
		{
			UAnimInstance* animInstnace = MeshComp->GetAnimInstance();

			animInstnace->Montage_Stop(0.2f);

			player->EndAttackMontage();
		}



	}
	// do nothing
	//else 
	// quit out of montage
}