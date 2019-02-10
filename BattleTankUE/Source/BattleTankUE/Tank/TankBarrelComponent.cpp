// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankBarrelComponent.h"


void UTankBarrelComponent::Elevate(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewElevation = FMath::Clamp<float>(RelativeRotation.Pitch + ElevationChange, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(NewElevation, 0, 0));

}

