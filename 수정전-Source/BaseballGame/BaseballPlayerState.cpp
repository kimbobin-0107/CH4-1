#include "BaseballPlayerState.h"
#include "Net/UnrealNetwork.h"

ABaseballPlayerState::ABaseballPlayerState()
{
    CurrentAttempt = 0;
    MaxAttempts = 3;
}

void ABaseballPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ABaseballPlayerState, CurrentAttempt);
}

FString ABaseballPlayerState::GetAttemptStatus() const
{
    return FString::Printf(TEXT("[%d / %d]"), CurrentAttempt, MaxAttempts);
}

void ABaseballPlayerState::AddAttempt()
{
    if (CurrentAttempt < MaxAttempts)
    {
        CurrentAttempt++;
    }
}

void ABaseballPlayerState::ResetAttempts()
{
    CurrentAttempt = 0;
}