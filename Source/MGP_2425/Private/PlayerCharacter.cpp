// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UPlayerBaseState.h"
#include "PlayerIdleState.h"
#include "PlayerWalkingState.h"
#include "PlayerSprintState.h"
#include "PlayerJumpState.h"
#include "PlayerFallingState.h"
#include "PlayerAttackState.h"
#include "TargetDummy.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

APlayerCharacter::APlayerCharacter()
{
    
    PrimaryActorTick.bCanEverTick = true;



}

void APlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    //set up inputs
    APlayerController* PlayerController = Cast<APlayerController>(GetController());
    if (PlayerController)
    {
        ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
        if (LocalPlayer)
        {
            UEnhancedInputLocalPlayerSubsystem* EILPS = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
            if (EILPS)
            {
                
                EILPS->AddMappingContext(inputMapping, 0);
            }
        }
    }
    idleState = NewObject<UPlayerIdleState>(this, UPlayerIdleState::StaticClass(), TEXT("IdleState"));
    walkState = NewObject<UPlayerWalkingState>(this, UPlayerWalkingState::StaticClass(), TEXT("WalkState"));
    sprintState = NewObject<UPlayerSprintState>(this, UPlayerSprintState::StaticClass(), TEXT("SprintState"));
    jumpState = NewObject<UPlayerJumpState>(this, UPlayerJumpState::StaticClass(), TEXT("JumpState"));
    fallState = NewObject<UPlayerFallingState>(this, UPlayerFallingState::StaticClass(), TEXT("FallState"));
    attackState = NewObject<UPlayerAttackState>(this, UPlayerAttackState::StaticClass(), TEXT("AttackState"));
    //

    //set the first state to idle
    SwitchState(idleState);


    //setting up stamina
    SetUpStats();
    

    //setting up sword for collision
    SetUpSword();
    
    
}


void APlayerCharacter::SetUpSword()
{
   
    swordBoxCol = Cast<UBoxComponent>(GetDefaultSubobjectByName(TEXT("SwordBoxCollider"))); // box collider
    if (swordBoxCol == nullptr) return;
    swordBoxCol->SetCollisionEnabled(ECollisionEnabled::QueryOnly); //setting sword collsion parameters
    swordBoxCol->SetGenerateOverlapEvents(true);
    //UE_LOG(LogTemp, Warning, TEXT("adding overlap"));
    if (swordBoxCol)
    {
        swordBoxCol->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnWeaponCollision); // making collision detection
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("swordBoxCol is nill"));
    }
    CloseWeaponCollider(); // starting sword with a closed colldier

}

void APlayerCharacter::SetUpStats()
{
    currentStamina = maxStamina;
}


void APlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    isGrounded = HandleGroundCheck(); // checking if player is grounded

    if (currentState != nullptr)
    {
        currentState->OnStateUpdate(DeltaTime); //updating state
        UPlayerBaseState* nextState = currentState->OnStateTransition(); // getting the next state from the current state transition return state
        if (nextState != currentState)
        {
            SwitchState(nextState); // if its a diferent state then  switch it the next one
        }
    }

    HandleStamina(DeltaTime); 

    BoolCheck();
}

void APlayerCharacter::BoolCheck()
{
    if (isGrounded) // disabling sprinting if requirments are met
    {
        if (!CanDoAction(sprintStamCost) && isSprinting)
        {
            DisableSprint();
        }
    }
    else
    {
        DisableSprint();
    }
}

void APlayerCharacter::HandleStamina(float DeltaTime)
{
    if (currentStamina < maxStamina) // can be filled up
    {
        stamTimer += DeltaTime; // stam timer is time since last stamina use

        if (stamTimer >= stamRegenCooldown)
        {
            //regen stam
            HandleRegenStam();
        }
    }
}

//stats

void APlayerCharacter::HandleRegenStam()
{
    currentStamina += stamRegenRate;
    if (currentStamina >= maxStamina)
    {
        currentStamina = maxStamina;
    }
}

void APlayerCharacter::HandleLoseStam(float val)
{
    currentStamina -= val;
    stamTimer = 0.0f;
}

bool APlayerCharacter::CanDoAction(float cost) // a check if player has enough stamina
{
    return currentStamina > cost;
}

bool APlayerCharacter::HandleGroundCheck() // assigning "isGrounded" bool for checks
{
    return !GetCharacterMovement()->IsFalling();

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) // player inputs
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (EnhancedInput)
    {

        EnhancedInput->BindAction(moveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::SetMovementInput);
        EnhancedInput->BindAction(moveAction, ETriggerEvent::Completed, this, &APlayerCharacter::ClearMovementInput);
        EnhancedInput->BindAction(lookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::CameraControl);
        EnhancedInput->BindAction(jumpAction, ETriggerEvent::Started, this, &APlayerCharacter::OnJumpPressed);

        EnhancedInput->BindAction(attackAction, ETriggerEvent::Triggered, this, &APlayerCharacter::HandleAttack);

        EnhancedInput->BindAction(sprintAction, ETriggerEvent::Triggered, this, &APlayerCharacter::EnableSprint);
        EnhancedInput->BindAction(sprintAction, ETriggerEvent::Completed, this, &APlayerCharacter::DisableSprint);
    }


}

void APlayerCharacter::EnableSprint()
{
    if (CanDoAction(sprintStamCost))
    {
        ToggleSprint(true);

    }
}

void APlayerCharacter::DisableSprint()
{
    ToggleSprint(false);
}

void APlayerCharacter::ToggleSprint(bool state)
{
    isSprinting = state;
    
}

bool APlayerCharacter::GetSprintFlag()
{
    return isSprinting;
}

void APlayerCharacter::ClearMovementInput()
{
    movementInput = FVector2D::ZeroVector;
}




void APlayerCharacter::SetMovementSpeed(float newVal)
{
    GetCharacterMovement()->MaxWalkSpeed = newVal;
}

float APlayerCharacter::GetSpeed()
{
    float speed = GetVelocity().Size();
    return speed;
}



void APlayerCharacter::MovePlayer(FVector dir, float value)
{
    if (Controller && value != 0.0f)
    {
        AddMovementInput(dir, value);


    }
}

FVector2D APlayerCharacter::GetMovementInput()
{
    return movementInput;
}

void APlayerCharacter::SetMovementInput(const FInputActionValue& Value)
{
    FVector2D input = Value.Get<FVector2D>();
    movementInput = input;
}

void APlayerCharacter::CameraControl(const FInputActionValue& Value)
{
    FVector2D LookAxis = Value.Get<FVector2D>();
    AddControllerYawInput(LookAxis.X);
    AddControllerPitchInput(LookAxis.Y);
    
}

void APlayerCharacter::OnJumpPressed()
{
    if (isGrounded && CanDoAction(jumpStamCost))
    {
        SwitchState(jumpState); 
       
    }
}



void APlayerCharacter::HandleAttack()
{
    if (isGrounded && CanDoAction(jumpStamCost))
    {
        comboAttacksDone += 1;
        comboKnockbackPower = comboAttacksDone * comboPowerMultiplier;
        if (!isAttacking)
        {
            SwitchState(attackState);
        }
        else if (isAttacking)
        {
            comboFlag = true;
        }

    }
    
}

//states

void APlayerCharacter::SwitchState(UPlayerBaseState* newState)
{
    if (newState == currentState)
    {
        //do nothing
        return;
    }

    if (GEngine)
    {
        FString txt = FString::Printf(TEXT("Switching State to %s"), *newState->GetName());
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, txt);
    }
    if (currentState != nullptr)
    {
        currentState->OnStateExit();
    }
    currentState = newState;
    if (currentState != nullptr)
    {
        currentState->OnStateEnter(this);
    }
}



void APlayerCharacter::EndAttackMontage()
{
    SwitchState(idleState);
}

void APlayerCharacter::OpenWeaponCollider()
{

    

    if (swordBoxCol != nullptr)
    {
        //UE_LOG(LogTemp, Warning, TEXT("Enabling Sword Collider"));
        
        swordBoxCol->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    }
}


void APlayerCharacter::CloseWeaponCollider()
{
    if (swordBoxCol != nullptr)
    {
        //UE_LOG(LogTemp, Warning, TEXT("Disable Sword Collider"));
        swordBoxCol->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    }
}

void APlayerCharacter::OnWeaponCollision(UPrimitiveComponent* swordC, AActor* actorHit, UPrimitiveComponent* actorComponentHit, int32 index, bool fromSweep, const FHitResult& sweep)
{
    
    if (actorHit == this) return;

    
    ATargetDummy* targetDummy = Cast<ATargetDummy>(actorHit);
    
    
    if (targetDummy)
    {
        FVector hitDirection = actorHit->GetActorLocation() - this->GetActorLocation();

        hitDirection.Normalize();

        targetDummy->OnHit(hitDirection, comboKnockbackPower);

        //play sound

        UGameplayStatics::PlaySoundAtLocation(GetWorld(), swordHitSound, GetActorLocation());

    }
}