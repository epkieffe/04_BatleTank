// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTank.h"
#include "Tank.h"
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

	auto HitLocation = FVector(0); //Out Parameter
	if (GetSightRayHitLocation(HitLocation)) //performs linetrace
	{
		GetControlledTank()->AimAt(HitLocation);
	};

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// translate crosshair position to pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);

	//deproject
	FVector TraceDirection;
	if (GetTraceDirection(ScreenLocation, TraceDirection))
	{
		GetLookVectorHitLocation(TraceDirection, HitLocation);
	}

	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector TraceDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (TraceDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	return false;
}

bool ATankPlayerController::GetTraceDirection(FVector2D ScreenLocation, FVector& TraceDirection) const
{
	FVector TraceStart; // To be discarded
	DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		TraceStart,
		TraceDirection);
	return true;
}
