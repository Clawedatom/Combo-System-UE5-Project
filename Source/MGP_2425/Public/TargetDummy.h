// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TargetDummy.generated.h"

UCLASS()
class MGP_2425_API ATargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	

	ATargetDummy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnHit(FVector hitDirection, float knockbackPower);

	void HandleKnockback(FVector knockbackVector);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dummy Fields")
	bool isHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dummy Fields")
	bool playSwordParticle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dummy Fields")
	float hitCooldown = 0.5f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dummy Fields")
	float hitTimer;

	//shake

	void HandleShake();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dummy Fields")
	float shakeAmount = 5.0f;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dummy Fields")
	FVector originalLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dummy Fields")
	UStaticMeshComponent* dummyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dummy Fields")
	UMaterialInterface* baseMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dummy Fields")
	UMaterialInstanceDynamic* matDynamic;

	UPROPERTY(VisibleAnywhere) 
	UStaticMeshComponent* meshComp;
	


	
};
