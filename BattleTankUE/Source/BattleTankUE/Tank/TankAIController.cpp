// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
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

void ATankAIController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { 
			UE_LOG(LogTemp, Warning, TEXT("Cannot find PossessedAITank: %s"), *GetName());
			return;
		}
		
		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
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
	if (!GetPlayerTank()) { 
		UE_LOG(LogTemp, Warning, TEXT("Cannot find PlayerTank"));
		return;
	}
	if (!ensure(ControlledTank)) { return; }
	FVector aim = GetPlayerTank()->GetActorLocation();
	AimingComponent->AimAt(aim);

	if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked) {
		//AimingComponent->Fire();
	}

	
	MoveToActor(GetPlayerTank(), AcceptanceRadius);
}

void ATankAIController::OnTankDeath() {
	if (GetPawn()) {
		GetPawn()->DetachFromControllerPendingDestroy();
	}
	UE_LOG(LogTemp, Warning, TEXT("TANK DED FROM AI CONTROLLER"));
}
