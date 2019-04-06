// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Mortar.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMortarDelegate);


UCLASS()
class BATTLETANKUE_API AMortar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMortar();

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

	FMortarDelegate OnDeath;
	
};
