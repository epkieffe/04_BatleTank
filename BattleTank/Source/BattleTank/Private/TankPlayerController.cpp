// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTank.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		//UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"));
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing: %s"), *ControlledTank->GetName());
	}
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("%s ticking"), *GetControlledTank()->GetName());
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; //Out Parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		// Calcualte trajectory to target
		// move barrel towards calcualted trajectory
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
	};

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	FVector TraceDirection;
	//find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D (ViewportSizeX*CrossHairXLocation,
		ViewportSizeY*CrossHairYLocation);
	
	//deproject
	if (GetLookDirection(ScreenLocation, TraceDirection))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Crosshair at: %s"), *ScreenLocation.ToString());
	}
	
	// return bool
	return true;	
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& TraceDirection) const
{
	FVector TraceStart; // To be discarded
	DeprojectScreenPositionToWorld(ScreenLocation.X,
		ScreenLocation.Y,
		TraceStart, //out
		TraceDirection);
	//DrawDebugLine
	(
		GetWorld(),
		TraceStart,
		TraceStart + (100.f*TraceDirection),
		FColor(255, 0, 0),
		false,
		0.1f,
		1,
		5.0f
	);
	return false;
}
