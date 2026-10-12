#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BaseballPlayerController.generated.h"

class UBaseballChatInput;

UCLASS()
class BASEBALL_API ABaseballPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void SetChatMessageString(const FString& InChatMessageString);
	void PrintChatMessageString(const FString& InChatMessageString);

	void ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString);

	void ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Baseball")
	void ServerRPCPrintChatMessageString(const FString& InChatMessageString);

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Baseball")
	void ClientRPCPrintChatMessageString(const FString& InChatMessageString);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBaseballChatInput> ChatInputWidgetClass;

	UPROPERTY()
	TObjectPtr<UBaseballChatInput> ChatInputWidgetInstance;

	FString ChatMessageString;
};