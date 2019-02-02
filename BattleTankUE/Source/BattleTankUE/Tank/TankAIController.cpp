// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay() {
	//UE_LOG(LogTemp, Warning, TEXT("AI Controller Tank  Reporting for duty: %s"), *GetControlledTank()->GetName());

	ATank* playerTank = GetPlayerTank();
	if (playerTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player Found by AI: %s"), *playerTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player NOT FOUND by: %s"), *GetControlledTank()->GetName());
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	if (!playerController) {
		return nullptr;
	}

	return Cast<ATank>(playerController->GetPawn());
}
