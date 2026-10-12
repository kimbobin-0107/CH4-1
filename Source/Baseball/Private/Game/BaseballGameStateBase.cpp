// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/BaseballGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/BaseballPlayerController.h"

void ABaseballGameStateBase::MulticastRPCBroadcastLoginMessage_Implementation(const FString& InNameString)
{
	if (HasAuthority() == false)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (IsValid(PC) == true)
		{
			ABaseballPlayerController* CXPC = Cast<ABaseballPlayerController>(PC);
			if (IsValid(CXPC) == true)
			{
				FString NotificationString = InNameString + TEXT(" has joined the game.");
				CXPC->PrintChatMessageString(NotificationString);
			}
		}
	}
}
