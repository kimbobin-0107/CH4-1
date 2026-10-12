#include "BaseballGameMode.h"
#include "BaseballPlayerState.h"
#include "Kismet/GameplayStatics.h"

ABaseballGameMode::ABaseballGameMode()
{
}

void ABaseballGameMode::BeginPlay()
{
    Super::BeginPlay();
    ResetGame();
}

void ABaseballGameMode::GenerateRandomNumbers()
{
    TArray<int32> Numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    // 무작위 섞기
    for (int32 i = Numbers.Num() - 1; i > 0; --i)
    {
        int32 j = FMath::RandRange(0, i);
        Numbers.Swap(i, j);
    }

    TargetNumber = FString::Printf(TEXT("%d%d%d"), Numbers[0], Numbers[1], Numbers[2]);
    UE_LOG(LogTemp, Warning, TEXT("Generated Answer: %s"), *TargetNumber);
}

bool ABaseballGameMode::IsValidInput(const FString& Input)
{
    // 3자리 숫자인지 확인
    if (Input.Len() != 3) return false;

    for (int32 i = 0; i < 3; ++i)
    {
        TCHAR c = Input[i];
        // 숫자가 아니거나 1~9 범위를 벗어나는지 (0 불가)
        if (!FChar::IsDigit(c) || c == '0') return false;
    }

    // 중복 숫자가 있는지 확인
    if (Input[0] == Input[1] || Input[0] == Input[2] || Input[1] == Input[2]) return false;

    return true;
}

FString ABaseballGameMode::CheckAnswer(const FString& Input)
{
    if (!IsValidInput(Input))
    {
        return TEXT("Invalid Input"); // 유효하지 않으면 기회 소진 안 함
    }

    // 플레이어 스테이트 가져와서 기회 증가 관리
    auto* PS = Cast<ABaseballPlayerState>(UGameplayStatics::GetPlayerState(this, 0));
    if (PS)
    {
        PS->AddAttempt();
    }

    int32 Strikes = 0;
    int32 Balls = 0;

    for (int32 i = 0; i < 3; ++i)
    {
        if (Input[i] == TargetNumber[i])
        {
            Strikes++;
        }
        else
        {
            for (int32 j = 0; j < 3; ++j)
            {
                if (i != j && Input[i] == TargetNumber[j])
                {
                    Balls++;
                }
            }
        }
    }

    // 3 스트라이크 승리 판정
    if (Strikes == 3)
    {
        UE_LOG(LogTemp, Warning, TEXT("VICTORY! Winner determined."));
        return TEXT("3S WIN!");
    }

    // 3회 시도 초과 무승부 판정
    if (PS && PS->CurrentAttempt >= PS->MaxAttempts)
    {
        UE_LOG(LogTemp, Warning, TEXT("DRAW! Max attempts reached."));
        FString Result = FString::Printf(TEXT("%dS %dB - DRAW"), Strikes, Balls);
        ResetGame(); // 리셋 시스템 연동
        return Result;
    }

    if (Strikes == 0 && Balls == 0)
    {
        return TEXT("OUT");
    }

    return FString::Printf(TEXT("%dS %dB"), Strikes, Balls);
}

void ABaseballGameMode::ResetGame()
{
    GenerateRandomNumbers();
    auto* PS = Cast<ABaseballPlayerState>(UGameplayStatics::GetPlayerState(this, 0));
    if (PS)
    {
        PS->ResetAttempts();
    }
    UE_LOG(LogTemp, Warning, TEXT("Game Reset Completed."));
}