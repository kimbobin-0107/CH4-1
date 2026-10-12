#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BaseballPlayerController.generated.h"

UCLASS()
class BASEBALLGAME_API ABaseballPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    // 클라이언트가 엔터를 쳐서 입력값을 보낼 때 호출하는 Server RPC 함수
    UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Baseball")
    void Server_SubmitGuess(const FString& GuessText);
};