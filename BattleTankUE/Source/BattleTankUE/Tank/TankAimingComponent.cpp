// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrelComponent.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "TankTurretComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (AmmoCount <= 0) {
		FiringStatus = EFiringStatus::Empty;
	}
	else if (FPlatformTime::Seconds() - LastFireTime < ReloadTimeInSeconds) {
		FiringStatus = EFiringStatus::Reloading;
	}
	else if(IsBarrelMoving()) {
		FiringStatus = EFiringStatus::Aiming;
	}
	else {
		FiringStatus = EFiringStatus::Locked;
	}
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel && Turret)) {
		return;
	}

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool foundSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OUT OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false, 0, 0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (foundSolution) {
		AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
	}
	else {
		// No Aim Found
	}
}

void UTankAimingComponent::Initialize(UTankBarrelComponent * BarrelToSet, UTankTurretComponent * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector TargetAimDirection) {
	if (!ensure(Barrel)) { return; }
	// difference between current barrel directions and aim direction
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator = TargetAimDirection.Rotation();
	FRotator Difference = AimRotator - BarrelRotation;

	Barrel->Elevate(Difference.Pitch);
}

bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(Barrel)) { return false; }
	return !Barrel->GetForwardVector().Equals(AimDirection, .01);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection) {
	if (!ensure(Turret)) { return;  }
	FRotator TurretRotation = Turret->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	float DifferenceYaw = AimRotator.Yaw - TurretRotation.Yaw;

	if (abs(DifferenceYaw) > 180) {
		Turret->Rotate(-DifferenceYaw);
	} else {
		Turret->Rotate(DifferenceYaw);
	}
}

void UTankAimingComponent::Fire()
{
	if (FiringStatus == EFiringStatus::Locked || FiringStatus == EFiringStatus::Aiming) {
		if (!ensure(Barrel && ProjectileBlueprint)) { return; }
		// spawn a projectile at the socket location on the barrel
		FVector SocketLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator SocketRotation = Barrel->GetSocketRotation(FName("Projectile"));
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SocketLocation, SocketRotation);

		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
		AmmoCount--;
	}
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const {
	return FiringStatus;
}

int32 UTankAimingComponent::GetAmmoCount() const {
	return AmmoCount;
}