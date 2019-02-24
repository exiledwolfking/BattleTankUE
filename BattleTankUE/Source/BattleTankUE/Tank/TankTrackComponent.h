// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrackComponent.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKUE_API UTankTrackComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:

	// sets throttle -1, 1
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
	
	// max force per track, in newtons
	// 40,000 = 40,000 kg * 10m/ss acceleration
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 800000;
};
