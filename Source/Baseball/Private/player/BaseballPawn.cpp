// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BaseballPawn.h"
#include "Baseball.h"

// Sets default values
ABaseballPawn::ABaseballPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseballPawn::BeginPlay()
{
	Super::BeginPlay();
	
	FString NetRoleString = BaseballFunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("CXPawn::BeginPlay() %s [%s]"), *BaseballFunctionLibrary::GetNetModeString(this), *NetRoleString);
	BaseballFunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}

// Called every frame
void ABaseballPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseballPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseballPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	FString NetRoleString = BaseballFunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("CXPawn::PossessedBy() %s [%s]"), *BaseballFunctionLibrary::GetNetModeString(this), *NetRoleString);
	BaseballFunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}

