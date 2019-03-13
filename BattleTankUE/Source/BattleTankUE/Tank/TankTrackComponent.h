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

	UTankTrackComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
public:

	// sets throttle -1, 1
	void SetThrottle(float Throttle);
	
	// max force per track, in newtons
	// 40,000 = 40,000 kg * 10m/ss acceleration
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000.0;
};
