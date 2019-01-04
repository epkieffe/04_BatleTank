// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void  UTankTurret::Rotate(FVector WishAngleWithDeltaTime) // encoded as yaw, pitch, time
{
	float DeltaTime = WishAngleWithDeltaTime.Z;
	
	float WishOmegaClamped = FMath::Clamp(
		(1 / DeltaTime) * (WishAngleWithDeltaTime.X - GetForwardVector().Rotation().Yaw),
		-MaxDegreesPerSecond,
		MaxDegreesPerSecond);

	AddRelativeRotation(FRotator(0, WishOmegaClamped * DeltaTime, 0));
}
