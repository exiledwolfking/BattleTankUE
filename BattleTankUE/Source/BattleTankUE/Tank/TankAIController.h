// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANKUE_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	ATank* GetControlledTank() const;

	ATank* GetPlayerTank() const;


	
};
