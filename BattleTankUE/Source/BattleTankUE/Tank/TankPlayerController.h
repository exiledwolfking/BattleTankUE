// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h"
#include "Image.h"
#include "Widget.h"
#include "UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * Responsible for helping the player aim
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKUE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingComponentRef);

	// UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* AimingComponent = nullptr;

private:

	virtual void SetPawn(APawn* InPawn) override;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	// float CrossHairYLocation = 0.25223;
	float CrossHairYLocation = 0.25;

	void AimAtCrosshair();
	bool GetSightRayHitLocation(FVector& OutHitLocation);

	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;

	bool GetLookVectorHitLocation(FVector& OutHitLocation, FVector LookDirection) const;

	FVector GetLineTraceStart() const;

	FVector GetLineTraceEnd(FVector LookDirection) const;

	UFUNCTION()
	void OnTankDeath();

};
