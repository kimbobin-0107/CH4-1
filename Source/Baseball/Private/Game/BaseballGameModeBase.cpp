#include "Game/BaseballGameModeBase.h"
#include "Game/BaseballGameStateBase.h"
#include "Kismet/GameplayStatics.h"

ABaseballGameModeBase::ABaseballGameModeBase()
{
	// 생성자에서 최초 랜덤 숫자 생성
	GenerateRandomNumbers();
}

void ABaseballGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	if (TargetNumber.IsEmpty())
	{
		GenerateRandomNumbers();
	}

	ABaseballGameStateBase* BaseballGameStateBase = GetGameState<ABaseballGameStateBase>();
	if (IsValid(BaseballGameStateBase) == true)
	{
		BaseballGameStateBase->MulticastRPCBroadcastLoginMessage(TEXT("Player"));
	}
}

void ABaseballGameModeBase::GenerateRandomNumbers()
{
	TArray<int32> Numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (int32 i = Numbers.Num() - 1; i > 0; --i)
	{
		int32 j = FMath::RandRange(0, i);
		Numbers.Swap(i, j);
	}

	TargetNumber = FString::Printf(TEXT("%d%d%d"), Numbers[0], Numbers[1], Numbers[2]);

	// 출력 로그로 정답 확인 가능
	UE_LOG(LogTemp, Warning, TEXT("=== [Baseball] Generated Target Number: %s ==="), *TargetNumber);
}

bool ABaseballGameModeBase::IsValidInput(const FString& Input) const
{
	if (Input.Len() != 3) return false;

	for (int32 i = 0; i < 3; ++i)
	{
		TCHAR c = Input[i];
		if (!FChar::IsDigit(c) || c == '0') return false;
	}

	if (Input[0] == Input[1] || Input[0] == Input[2] || Input[1] == Input[2]) return false;

	return true;
}

FString ABaseballGameModeBase::CheckAnswer(const FString& Input)
{
	if (!IsValidInput(Input))
	{
		return TEXT("Invalid Input");
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

	if (Strikes == 3)
	{
		GenerateRandomNumbers();
		return TEXT("3S WIN!");
	}

	if (Strikes == 0 && Balls == 0)
	{
		return TEXT("OUT");
	}

	return FString::Printf(TEXT("%dS %dB"), Strikes, Balls);
}

void ABaseballGameModeBase::ResetGame()
{
	GenerateRandomNumbers();
}