// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrackComponent;

/**
 * Responsible for driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKUE_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	// Throw of +1 is forward. -1 is backward
	UFUNCTION(BlueprintCallable, Category="Movement")
	void IntendMoveForward(float Throw);


	// Throw of +1 is right. -1 is left
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void IntendTurn(float Throw);


	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankTrackComponent* LeftTrackToSet, UTankTrackComponent* RightTrackToSet);
	
private:
	UTankTrackComponent* LeftTrack = nullptr;
	UTankTrackComponent* RightTrack = nullptr;

};
