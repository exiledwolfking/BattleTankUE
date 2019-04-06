// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (!GetPawn()) { return; }
	UTankAimingComponent* AimingComponentToSet = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponentToSet)) { return; }
	FoundAimingComponent(AimingComponentToSet);
	AimingComponent = AimingComponentToSet;
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimAtCrosshair();
}

void ATankPlayerController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
	}
}

void ATankPlayerController::AimAtCrosshair()
{
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; // out parameter

	// get world location of linetrace through crosshair
	bool bGotHitLocation = GetSightRayHitLocation(OUT HitLocation);
	if (bGotHitLocation) {
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		// tell controlled tank to aim at this point
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation)
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	int32 XLocation = ViewportSizeX * CrossHairXLocation;
	int32 YLocation = ViewportSizeY * CrossHairYLocation;

	FVector2D CrossHairLocation = FVector2D(XLocation, YLocation);

	FVector LookDirection;
	if (GetLookDirection(CrossHairLocation, LookDirection)) {
		// Line trace along LookDirection and see if anything is hit

		return GetLookVectorHitLocation(OUT OutHitLocation, LookDirection);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D CrossHairLocation, FVector& LookDirection) const
{
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(CrossHairLocation.X, CrossHairLocation.Y, WorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& OutHitLocation, FVector LookDirection) const
{
	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(
			OUT HitResult,
			GetLineTraceStart(),
			GetLineTraceEnd(LookDirection),
			ECollisionChannel::ECC_Camera
	)) {
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0);
	return false;
}

FVector ATankPlayerController::GetLineTraceStart() const {
	return PlayerCameraManager->GetCameraLocation();
	// return GetControlledTank()->GetTargetLocation() + FVector(300.f, 0, 170.f);
}

FVector ATankPlayerController::GetLineTraceEnd(FVector LookDirection) const {
	return GetLineTraceStart() + (LookDirection * LineTraceRange);
}

void ATankPlayerController::OnTankDeath() {
	// UE_LOG(LogTemp, Warning, TEXT("TANK DED FROM PLAYER CONTROLLER"));
	StartSpectatingOnly();
}

