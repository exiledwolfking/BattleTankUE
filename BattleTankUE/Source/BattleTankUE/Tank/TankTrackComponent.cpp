// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"


UTankTrackComponent::UTankTrackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrackComponent::BeginPlay() {
	Super::BeginPlay();
	OnComponentHit.AddDynamic( this, &UTankTrackComponent::OnHit);
}

// Called every frame
void UTankTrackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	if (!ensure(TankRoot)) { return; }

	// Calculate the slippage speed - cross product
	FVector RightVector = TankRoot->GetRightVector();
	FVector Velocity = TankRoot->GetComponentVelocity();
	float SlippageSpeed = FVector::DotProduct(Velocity, RightVector);

	// find the required acceleration this frame to correct
	FVector CorrectionAcceleration = - SlippageSpeed / DeltaTime * TankRoot->GetRightVector();

	// calculate and apply sideways force F = ma/2 (2 tracks)
	FVector CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2;
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrackComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	UE_LOG(LogTemp, Warning, TEXT("HitEvent: %s"), *NormalImpulse.ToString());
}


void UTankTrackComponent::SetThrottle(float Throttle) {
	//TODO: Throttle value to -1, +1
	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

