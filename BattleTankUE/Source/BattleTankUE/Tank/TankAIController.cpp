// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay() {
	//UE_LOG(LogTemp, Warning, TEXT("AI Controller Tank  Reporting for duty: %s"), *GetControlledTank()->GetName());
	Super::BeginPlay();

	SetActorTickEnabled(true);

	UTankAimingComponent* AimingComponentToSet = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponentToSet)) { return; }
	AimingComponent = AimingComponentToSet;
}

APawn* ATankAIController::GetPlayerTank() const
{
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(playerController)) {
		return nullptr;
	}

	return playerController->GetPawn();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* ControlledTank = GetPawn();
	if (!ensure(GetPlayerTank() && ControlledTank)) { return; }
	FVector aim = GetPlayerTank()->GetActorLocation();
	AimingComponent->AimAt(aim);

	if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked) {
		AimingComponent->Fire();
	}

	
	MoveToActor(GetPlayerTank(), AcceptanceRadius);
}
