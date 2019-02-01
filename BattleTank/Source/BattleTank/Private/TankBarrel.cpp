// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void  UTankBarrel::Elevate(FVector WishAngleWithDeltaTime) // encoded as yaw, pitch, time
{
	float DeltaTime = WishAngleWithDeltaTime.Z;

	auto RelativeElevation = GetForwardVector().Rotation().Pitch; // TODO fix relative elevation

	auto SocketElevation = GetSocketRotation(FName("Barrel")).Pitch;

	float WishAngleClamped = FMath::Clamp(
		WishAngleWithDeltaTime.Y,
		MinElevationDegrees,
		MaxElevationDegrees);

	float WishOmegaClamped = FMath::Clamp(
		(1/ DeltaTime) * (WishAngleClamped - RelativeElevation),
		-MaxDegreesPerSecond,
		MaxDegreesPerSecond);

	AddRelativeRotation(FRotator(WishOmegaClamped * DeltaTime, 0, 0));
}
