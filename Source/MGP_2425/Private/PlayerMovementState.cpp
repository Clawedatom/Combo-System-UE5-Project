


#include "PlayerMovementState.h"



#include "PlayerCharacter.h"

UPlayerMovementState::UPlayerMovementState()
{
    
}

void UPlayerMovementState::OnStateEnter(APlayerCharacter* _player)
{
    Super::OnStateEnter(_player);
    
}

void UPlayerMovementState::OnStateUpdate(float DeltaSeconds)
{
    Super::OnStateUpdate(DeltaSeconds);

    if (!player) return;

    FVector2D moveInput = player->GetMovementInput();

    if (player->GetController())
    {
        const FRotator Rotation = player->GetController()->GetControlRotation();
        const FRotator Yaw(0, Rotation.Yaw, 0);

        const FVector Forward = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
        const FVector Right = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);

        

        player->MovePlayer(Forward, moveInput.Y);
        player->MovePlayer(Right, moveInput.X);
    }



}

void UPlayerMovementState::OnStateExit()
{
    Super::OnStateExit();
    
}

UPlayerBaseState* UPlayerMovementState::OnStateTransition()
{
    UPlayerBaseState* nextState = Super::OnStateTransition();


    
    if (player->isGrounded)
    {
        if (player->GetMovementInput() == FVector2D::ZeroVector) //if no input return to idle state
        {
            return player->idleState;
        }

        if (player->GetMovementInput().Size() > 0.0f) //if moving and sprinting flag is true
        {
            if (player->GetSprintFlag())
            {
                return player->sprintState;
            }
            else
            {
                return player->walkState;
            }
        }
    }
    return nextState;
}