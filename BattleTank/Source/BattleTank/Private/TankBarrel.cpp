// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Engine/World.h"


void  UTankBarrel::Elevate(float WishAngleDeltaDegrees)
{
	float WishAngleClamped = FMath::Clamp(
		WishAngleDeltaDegrees,
		MinElevationDegrees,
		MaxElevationDegrees);
	float WishOmegaClamped = FMath::Clamp(
		WishAngleClamped * GetWorld()->DeltaTimeSeconds,
		-MaxDegreesPerSecond,
		MaxDegreesPerSecond);

	AddRelativeRotation(FRotator(WishOmegaClamped, 0, 0));

}
