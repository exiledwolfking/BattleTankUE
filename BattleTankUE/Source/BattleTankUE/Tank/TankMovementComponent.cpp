// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrackComponent.h"


void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!ensure(LeftTrack && RightTrack)) { return; }
	float clampedThrow = FMath::Clamp<float>(Throw, -1.0, 1.0);
	LeftTrack->SetThrottle(clampedThrow);
	RightTrack->SetThrottle(clampedThrow);
}

void UTankMovementComponent::IntendTurn(float Throw) {
	if (!ensure(LeftTrack && RightTrack)) { return; }
	float clampedThrow = FMath::Clamp<float>(Throw, -1.0, 1.0);
	LeftTrack->SetThrottle(clampedThrow);
	RightTrack->SetThrottle(-clampedThrow);
}

void UTankMovementComponent::Initialize(UTankTrackComponent * LeftTrackToSet, UTankTrackComponent * RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	// UE_LOG(LogTemp, Warning, TEXT("%s moving towards %s"), *name, *(AIForwardIntention.ToString()));

	float DotProduct = FVector::DotProduct(TankForward, AIForwardIntention);
	FVector CrossProduct = FVector::CrossProduct(AIForwardIntention, TankForward);

	IntendMoveForward(DotProduct);
	IntendTurn(CrossProduct.Z);
}
