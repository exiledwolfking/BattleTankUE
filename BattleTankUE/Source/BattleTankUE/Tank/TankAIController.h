// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANKUE_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// How close the AI can get to the player
	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRadius = 1000;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* AimingComponent = nullptr;
	
private:
	APawn* GetPlayerTank() const;
};
