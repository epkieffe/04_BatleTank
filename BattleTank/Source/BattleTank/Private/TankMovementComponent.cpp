// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet && RightTrackToSet)) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// Replacing Super functionality, no need to call
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIWishDirection = MoveVelocity.GetSafeNormal();
	
	WishForward(FVector::DotProduct(AIWishDirection, TankForward));
	WishTurn(FVector::CrossProduct(AIWishDirection, TankForward).Z);
}

void UTankMovementComponent::WishForward(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::WishTurn(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}
