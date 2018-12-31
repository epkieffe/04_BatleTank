// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Runtime/Engine/Classes/Engine/World.h"


void  UTankTurret::Rotate(float WishAngleDeltaDegrees)
{
	float WishOmegaClamped = FMath::Clamp(
		WishAngleDeltaDegrees * GetWorld()->DeltaTimeSeconds,
		-MaxDegreesPerSecond,
		MaxDegreesPerSecond);

	AddRelativeRotation(FRotator(0, WishOmegaClamped, 0));

}


