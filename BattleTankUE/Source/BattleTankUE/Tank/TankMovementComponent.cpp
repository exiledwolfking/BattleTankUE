// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrackComponent.h"


void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!RightTrack || !LeftTrack) { return; }
	float clampedThrow = FMath::Clamp<float>(Throw, -1.0, 1.0);
	LeftTrack->SetThrottle(clampedThrow);
	RightTrack->SetThrottle(clampedThrow);
}

void UTankMovementComponent::IntendTurn(float Throw) {
	if (!LeftTrack || !RightTrack) { return; }
	float clampedThrow = FMath::Clamp<float>(Throw, -1.0, 1.0);
	LeftTrack->SetThrottle(clampedThrow);
	RightTrack->SetThrottle(-clampedThrow);
}

void UTankMovementComponent::Initialize(UTankTrackComponent * LeftTrackToSet, UTankTrackComponent * RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}
