// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankTurretComponent.h"
#include "TankBarrelComponent.h"
#include "Engine/World.h"

void ATank::SetBarrelReference(UTankBarrelComponent* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurretComponent* TurretToSet) {
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	UE_LOG(LogTemp, Warning, TEXT("%s Firing"), *GetName());

	if (Barrel && IsReloaded) {

		// spawn a projectile at the socket location on the barrel
		FVector SocketLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator SocketRotation = Barrel->GetSocketRotation(FName("Projectile"));
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SocketLocation, SocketRotation);

		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation) {
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}
