// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Runtime/Engine/Classes/Engine/World.h"


void  UTankTurret::Rotate(float WishAngleDeltaDegrees)
{
	float WishOmegaClamped = FMath::Clamp(
		(1 / GetWorld()->DeltaTimeSeconds) * WishAngleDeltaDegrees,
		-MaxDegreesPerSecond,
		MaxDegreesPerSecond);

	AddRelativeRotation(FRotator(0, WishOmegaClamped * GetWorld()->DeltaTimeSeconds, 0));

}


