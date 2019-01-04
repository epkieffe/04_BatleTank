// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void  UTankBarrel::Elevate(FVector WishAngleWithDeltaTime) // encoded as yaw, pitch, time
{
	float DeltaTime = WishAngleWithDeltaTime.Z;

	float WishAngleClamped = FMath::Clamp(
		WishAngleWithDeltaTime.Y,
		MinElevationDegrees,
		MaxElevationDegrees);

	float WishOmegaClamped = FMath::Clamp(
		(1/ DeltaTime) * (WishAngleClamped - GetForwardVector().Rotation().Pitch),
		-MaxDegreesPerSecond,
		MaxDegreesPerSecond);

	AddRelativeRotation(FRotator(WishOmegaClamped * DeltaTime, 0, 0));
}
