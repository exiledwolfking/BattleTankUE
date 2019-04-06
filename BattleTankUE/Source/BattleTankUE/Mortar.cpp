// Fill out your copyright notice in the Description page of Project Settings.

#include "Mortar.h"


// Sets default values
AMortar::AMortar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

float AMortar::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamageAmountInt = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamageAmountInt, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0) {
		OnDeath.Broadcast();
	}
	return DamageToApply;
}

//float AMortar::GetHealthPercent() const
//{
	//return (float)CurrentHealth / (float)StartingHealth;
//}


