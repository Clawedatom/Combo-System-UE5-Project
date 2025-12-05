// Fill out your copyright notice in the Description page of Project Settings.

#include "TargetDummy.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/StaticMeshComponent.h"



ATargetDummy::ATargetDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATargetDummy::BeginPlay()
{
	Super::BeginPlay();

	UStaticMeshComponent* DummyMesh = FindComponentByClass<UStaticMeshComponent>();
	if (!DummyMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find UStaticMeshComponent"));
		return;
	}

	
	UMaterialInterface* BaseMaterial = DummyMesh->GetMaterial(0);
	if (!BaseMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("No base material found on mesh slot 0"));
		return;
	}

	
	matDynamic = UMaterialInstanceDynamic::Create(BaseMaterial, this);
	if (!matDynamic)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create dynamic material instance"));
		return;
	}

	
	DummyMesh->SetMaterial(0, matDynamic);

	dummyMesh = DummyMesh;
}

// Called every frame
void ATargetDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isHit)
	{
		hitTimer += DeltaTime;
		HandleShake();


		if (matDynamic)
		{
			matDynamic->SetVectorParameterValue("BaseColour", FLinearColor::Red);
		
		}

		if (hitTimer >= hitCooldown)
		{
			isHit = false;
			SetActorLocation(originalLocation);
			

			if (matDynamic)
			{
				FLinearColor clear = FLinearColor(0.f, 0.f, 0.f, 0.f);
				matDynamic->SetVectorParameterValue("BaseColour", clear);
			}
		}
	}

}

void ATargetDummy::HandleShake()
{
	FVector CurrentLocation = GetActorLocation();
	FVector RandomOffset = FVector(FMath::RandRange(-shakeAmount, shakeAmount),FMath::RandRange(-shakeAmount, shakeAmount),FMath::RandRange(-shakeAmount, shakeAmount)); // random shake

	
	SetActorLocation(CurrentLocation + RandomOffset);
}

void ATargetDummy::OnHit(FVector hitDirection, float knockbackPower)
{
	if (isHit) return; // being hit has a cooldown
	UE_LOG(LogTemp, Warning, TEXT("I Am %s And Ive Been Hit!"), *this->GetClass()->GetName());
	isHit = true;
	hitTimer = 0.0f;

	originalLocation = this->GetActorLocation();
	//HandleKnockback(hitDirection * knockbackPower);
	playSwordParticle = true;

}

void ATargetDummy::HandleKnockback(FVector knockbackVector)
{
	UPrimitiveComponent* primComp = Cast<UPrimitiveComponent>(GetRootComponent());

	if (primComp != nullptr)
	{
		knockbackVector.Z = 0.0;
		primComp->AddImpulse(knockbackVector, NAME_None, true);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Error with knockback"));
	}
}