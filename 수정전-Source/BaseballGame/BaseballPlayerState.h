#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BaseballPlayerState.generated.h"

UCLASS()
class BASEBALLGAME_API ABaseballPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    ABaseballPlayerState();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(Replicated, BlueprintReadWrite, Category = "Baseball")
    int32 CurrentAttempt;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Baseball")
    int32 MaxAttempts;

    UFUNCTION(BlueprintCallable, Category = "Baseball")
    FString GetAttemptStatus() const;

    UFUNCTION(BlueprintCallable, Category = "Baseball")
    void AddAttempt();

    UFUNCTION(BlueprintCallable, Category = "Baseball")
    void ResetAttempts();
};