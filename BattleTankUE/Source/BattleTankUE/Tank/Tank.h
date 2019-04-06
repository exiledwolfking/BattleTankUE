// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANKUE_API ATank : public APawn
{
	GENERATED_BODY()

	ATank();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	int32 CurrentHealth;

	// virtual void BeginPlay() override;

public:
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		class AController * EventInstigator,
		AActor * DamageCauser) override;

	//UFUNCTION(BlueprintCallable, Category = "Health")
	//float GetHealthPercent() const;

	FTankDelegate OnDeath;
};
