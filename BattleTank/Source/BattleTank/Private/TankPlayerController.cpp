// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// TODO Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(
			this,
			&ATankPlayerController::OnPossessedTankDeath
		);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	auto HitLocation = FVector(0); //Out Parameter
	if (GetSightRayHitLocation(HitLocation)) //performs linetrace
	{
		AimingComponent->AimAt(HitLocation);
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
		return GetLookVectorHitLocation(TraceDirection, HitLocation);
	}

	return false;
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
		ECollisionChannel::ECC_WorldStatic)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else
	{
		return false;
	}
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
