#include "BaseballPlayerController.h"
#include "BaseballGameMode.h"
#include "BaseballPlayerState.h"
#include "Kismet/GameplayStatics.h"

void ABaseballPlayerController::Server_SubmitGuess_Implementation(const FString& GuessText)
{
    // 서버(GameMode)에서만 실행됨
    if (auto* GM = Cast<ABaseballGameMode>(UGameplayStatics::GetGameMode(this)))
    {
        auto* PS = GetPlayerState<ABaseballPlayerState>();
        if (PS)
        {
            // 수정된 GameMode의 CheckAnswer 호출
            FString Result = GM->CheckAnswer(GuessText, PS);

            UE_LOG(LogTemp, Log, TEXT("Player Submitted: %s -> Result: %s"), *GuessText, *Result);
        }
    }
}