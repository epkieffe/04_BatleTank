// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Engine/World.h"


void  UTankBarrel::Elevate(float WishAngleDeltaDegrees)
{
	float WishOmegaClamped = FMath::Clamp(
		(1/ GetWorld()->DeltaTimeSeconds) * WishAngleDeltaDegrees,
		-MaxDegreesPerSecond,
		MaxDegreesPerSecond);

	AddRelativeRotation(FRotator(WishOmegaClamped * GetWorld()->DeltaTimeSeconds, 0, 0));

}
