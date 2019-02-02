// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	GetControlledTank();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimAtCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair() {
	if (!GetControlledTank()) {
		return;
	}

	FVector HitLocation; // out parameter

	// get world location of linetrace through crosshair
	if (GetSightRayHitLocation(OUT HitLocation)) {
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		// tell controlled tank to aim at this point
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) {
	/*FStringClassReference PlayerUIWidgetClassRef(TEXT("/Game/UI/PlayerUI_BP.PlayerUI_BP"));
	if (UClass* MyWidgetClass = PlayerUIWidgetClassRef.TryLoadClass<UUserWidget>())
	{
		UUserWidget* MyWidget = CreateWidget<UUserWidget>(GetWorld(), MyWidgetClass);
		// Do stuff with MyWidget
	}*/
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	int32 XLocation = ViewportSizeX * CrossHairXLocation;
	int32 YLocation = ViewportSizeY * CrossHairYLocation;

	FVector2D CrossHairLocation = FVector2D(XLocation, YLocation);
	UE_LOG(LogTemp, Warning, TEXT("Aim Position: %s"), *CrossHairLocation.ToString());
	return false;
}

