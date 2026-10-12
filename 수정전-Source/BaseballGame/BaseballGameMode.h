#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseballGameMode.generated.h"

UCLASS()
class BASEBALLGAME_API ABaseballGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ABaseballGameMode();

    virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadWrite, Category = "Baseball")
    FString TargetNumber;

    UFUNCTION(BlueprintCallable, Category = "Baseball")
    void GenerateRandomNumbers();

    UFUNCTION(BlueprintCallable, Category = "Baseball")
    bool IsValidInput(const FString& Input);

    UFUNCTION(BlueprintCallable, Category = "Baseball")
    FString CheckAnswer(const FString& Input);

    UFUNCTION(BlueprintCallable, Category = "Baseball")
    void ResetGame();
};