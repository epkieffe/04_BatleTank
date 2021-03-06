// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void  UTankTurret::Rotate(FVector WishAngleWithDeltaTime) // encoded as yaw, pitch, time
{
	float DeltaTime = WishAngleWithDeltaTime.Z;
	float CorrectedDeltaAngle = WishAngleWithDeltaTime.X - GetForwardVector().Rotation().Yaw;
	float Pitch = GetForwardVector().Rotation().Pitch;

	// these two if statements ensure "short" travel
	if (CorrectedDeltaAngle > 180)
	{
		CorrectedDeltaAngle = CorrectedDeltaAngle - 360;
	}
	else if (CorrectedDeltaAngle < -180)
	{
		CorrectedDeltaAngle = CorrectedDeltaAngle + 360;
	}
	
	float WishOmegaClamped = FMath::Clamp(
		(1 / DeltaTime) * CorrectedDeltaAngle,
		-MaxDegreesPerSecond,
		MaxDegreesPerSecond);

	AddRelativeRotation(FRotator(0, WishOmegaClamped * DeltaTime, 0));
}
