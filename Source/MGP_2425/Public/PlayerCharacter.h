

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"  
#include "InputActionValue.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Components/BoxComponent.h"
#include "PlayerCharacter.generated.h"

class UPlayerBaseState;



UCLASS()
class MGP_2425_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	APlayerCharacter();


	//states
	void SwitchState(UPlayerBaseState* newState);




protected:
	
	virtual void BeginPlay() override;



public:


	
	virtual void Tick(float DeltaTime) override;


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//getters
	float GetSpeed();

	FVector2D GetMovementInput();
	void SetMovementInput(const FInputActionValue& Value);



	void MovePlayer(FVector dir, float value);




	void CameraControl(const FInputActionValue& Value);
	void OnJumpPressed();

	void HandleAttack();


	void ClearMovementInput();


	bool HandleGroundCheck();

	//player bools
	void BoolCheck();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player bools")
	bool isSprinting;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player bools")
	bool isGrounded;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player bools")
	bool isAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player bools")
	bool comboFlag;

	//ground check
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Raycasts")
	float groundRayDist = 3.0f;


	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* inputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* moveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* lookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* sprintAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* jumpAction;


	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* attackAction;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* camera;


	

	//states
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "States")
	UPlayerBaseState* currentState;

	UPlayerBaseState* GetCurrentState() const { return currentState; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "States")
	UPlayerBaseState* idleState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "States")
	UPlayerBaseState* walkState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "States")
	UPlayerBaseState* sprintState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "States")
	UPlayerBaseState* jumpState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "States")
	UPlayerBaseState* fallState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "States")
	UPlayerBaseState* attackState;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	FVector2D movementInput;

	//stats
	void SetUpStats();

	void HandleStamina(float DeltaTime);

	void HandleRegenStam();
	
	void HandleLoseStam(float val);

	bool CanDoAction(float cost);

	void SetMovementSpeed(float newVal);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stamina")
	float currentStamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina")
	float maxStamina = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stamina")
	float stamTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stamina")
	float stamRegenRate = 0.5f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stamina")
	float stamRegenCooldown = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina")
	float sprintStamCost = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina")
	float jumpStamCost = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina")
	float attackStamCost = 15.0f;
	//vars
	void EnableSprint();
	void DisableSprint();

	void ToggleSprint(bool state);

	bool GetSprintFlag();




	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats")
	float movementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats")
	float walkSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats")
	float sprintSpeed = 1000.0f;

	UPROPERTY()
	float meshRotOffset = -90.0f;


	
	//anim
	void EndAttackMontage();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* attackMontage;

	//sword

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	UBoxComponent* swordBoxCol;

	void SetUpSword();

	void OpenWeaponCollider();

	void CloseWeaponCollider();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void OnWeaponCollision(UPrimitiveComponent* swordC,AActor* actorHit,UPrimitiveComponent* actorComponentHit,int32 index,bool fromSweep,const FHitResult& sweep);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	float comboKnockbackPower;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float comboPowerMultiplier = 5.0f;;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float comboAttacksDone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* swordHitSound;
};

