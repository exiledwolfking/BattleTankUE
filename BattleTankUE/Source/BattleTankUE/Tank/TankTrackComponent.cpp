// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankTrackComponent.h"


UTankTrackComponent::UTankTrackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrackComponent::BeginPlay() {
	Super::BeginPlay();
	OnComponentHit.AddDynamic( this, &UTankTrackComponent::OnHit);
}

void UTankTrackComponent::ApplySidewaysForce()
{
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	if (!ensure(TankRoot)) { return; }

	float DeltaTime = GetWorld()->GetDeltaSeconds();

	// Calculate the slippage speed - cross product
	FVector RightVector = TankRoot->GetRightVector();
	FVector Velocity = TankRoot->GetComponentVelocity();
	float SlippageSpeed = FVector::DotProduct(Velocity, RightVector);

	// find the required acceleration this frame to correct
	FVector CorrectionAcceleration = -SlippageSpeed / DeltaTime * TankRoot->GetRightVector();

	// calculate and apply sideways force F = ma/2 (2 tracks)
	FVector CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2;
	TankRoot->AddForce(CorrectionForce);
}
 
void UTankTrackComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}


void UTankTrackComponent::SetThrottle(float Throttle) {
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrackComponent::DriveTrack()
{
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

