#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseballGameModeBase.generated.h"

UCLASS()
class BASEBALL_API ABaseballGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABaseballGameModeBase();

	virtual void OnPostLogin(AController* NewPlayer) override;

	UPROPERTY(BlueprintReadWrite, Category = "Baseball")
	FString TargetNumber;

	UFUNCTION(BlueprintCallable, Category = "Baseball")
	void GenerateRandomNumbers();

	UFUNCTION(BlueprintCallable, Category = "Baseball")
	bool IsValidInput(const FString& Input) const;

	UFUNCTION(BlueprintCallable, Category = "Baseball")
	FString CheckAnswer(const FString& Input);

	UFUNCTION(BlueprintCallable, Category = "Baseball")
	void ResetGame();
};