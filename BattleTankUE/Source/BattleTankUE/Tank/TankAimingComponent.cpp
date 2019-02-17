// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrelComponent.h"
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

	// ...
	
}


void UTankAimingComponent::SetBarrelReference(UTankBarrelComponent* BarrelToSet)
{
	if (!BarrelToSet) {
		return;
	}
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurretComponent* TurretToSet) {
	if (!TurretToSet) {
		return;
	}
	Turret = TurretToSet;
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	FString OurTankName = GetOwner()->GetName();

	if (!Barrel || !Turret) {
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
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();

		UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *OurTankName, *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%s No Aim found"));
	}


}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {

	// difference between current barrel directions and aim direction
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator Difference = AimRotator - BarrelRotation;

	Barrel->Elevate(Difference.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection) {
	FRotator TurretRotation = Turret->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator Difference = AimRotator - TurretRotation;

	Turret->Rotate(Difference.Yaw);
}


