#include "player/BaseballPlayerController.h"
#include "UI/BaseballChatInput.h"
#include "Game/BaseballGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Baseball.h"

void ABaseballPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() == true)
	{
		FInputModeUIOnly InputModeUIOnly;
		SetInputMode(InputModeUIOnly);

		if (IsValid(ChatInputWidgetClass) == true)
		{
			ChatInputWidgetInstance = CreateWidget<UBaseballChatInput>(this, ChatInputWidgetClass);
			if (IsValid(ChatInputWidgetInstance) == true)
			{
				ChatInputWidgetInstance->AddToViewport();
			}
		}
	}
}

void ABaseballPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;

	if (IsLocalController() == true)
	{
		ServerRPCPrintChatMessageString(InChatMessageString);
	}
}

void ABaseballPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	BaseballFunctionLibrary::MyPrintString(this, InChatMessageString, 10.f);
}

void ABaseballPlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}

void ABaseballPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	FString FinalMessage = InChatMessageString;

	if (auto* GM = Cast<ABaseballGameModeBase>(UGameplayStatics::GetGameMode(this)))
	{
		FString GameResult = GM->CheckAnswer(InChatMessageString);
		FinalMessage = FString::Printf(TEXT("입력: %s -> 결과: %s"), *InChatMessageString, *GameResult);
	}

	for (TActorIterator<ABaseballPlayerController> It(GetWorld()); It; ++It)
	{
		ABaseballPlayerController* CXPlayerController = *It;
		if (IsValid(CXPlayerController) == true)
		{
			CXPlayerController->ClientRPCPrintChatMessageString(FinalMessage);
		}
	}
}