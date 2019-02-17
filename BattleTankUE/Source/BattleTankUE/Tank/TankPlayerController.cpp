// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// GetControlledTank();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimAtCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetControlledTank()) {
		return;
	}

	FVector HitLocation; // out parameter

	// get world location of linetrace through crosshair
	if (GetSightRayHitLocation(OUT HitLocation)) {
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		// tell controlled tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);
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

		if (GetLookVectorHitLocation(OUT OutHitLocation, LookDirection)) {
			return true;
		}
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
			ECollisionChannel::ECC_Visibility
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

