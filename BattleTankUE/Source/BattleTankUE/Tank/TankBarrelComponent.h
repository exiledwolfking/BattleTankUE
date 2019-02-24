// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrelComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKUE_API UTankBarrelComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward movement
	// +1 is max upward movement
	void Elevate(float);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 5;
	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevationDegrees = 40;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinElevationDegrees = 0;
};
