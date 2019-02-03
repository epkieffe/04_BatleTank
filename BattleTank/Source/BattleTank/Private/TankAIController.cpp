// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// TODO Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(
			this,
			&ATankAIController::OnPossessedTankDeath
		);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!ensure(GetPawn())) { return; } // TODO remove ensure if ok
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!GetPawn()) { return; }
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	
	if (PlayerTank)
	{
		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);

		// Aim at the player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
		if (AimingComponent->IsBarrelLocked())
		AimingComponent->Fire();
	}
}
