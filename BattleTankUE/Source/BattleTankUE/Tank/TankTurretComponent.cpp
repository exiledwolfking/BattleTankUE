// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurretComponent.h"
#include "Engine/World.h"

void UTankTurretComponent::Rotate(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float YawChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewYaw = RelativeRotation.Yaw + YawChange;

	SetRelativeRotation(FRotator(0, NewYaw, 0));
}


