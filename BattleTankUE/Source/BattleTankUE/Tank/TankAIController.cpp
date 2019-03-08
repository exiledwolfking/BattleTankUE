// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay() {
	//UE_LOG(LogTemp, Warning, TEXT("AI Controller Tank  Reporting for duty: %s"), *GetControlledTank()->GetName());
	Super::BeginPlay();

	SetActorTickEnabled(true);
	ATank* playerTank = GetPlayerTank();
	if (ensure(playerTank)) {
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
	if (!ensure(playerController)) {
		return nullptr;
	}

	return Cast<ATank>(playerController->GetPawn());
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!ensure(GetControlledTank() && GetPlayerTank())) {
		return;
	}
	FVector aim = GetPlayerTank()->GetActorLocation();
	GetControlledTank()->AimAt(aim);
	// GetControlledTank()->Fire();
	
	MoveToActor(GetPlayerTank(), AcceptanceRadius);
}
