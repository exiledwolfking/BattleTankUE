// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurretComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKUE_API UTankTurretComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max counter-clockwise movement
	// +1 is max clockwise movement
	void Rotate(float);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 30;
	
};
