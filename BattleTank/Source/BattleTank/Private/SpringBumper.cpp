// Fill out your copyright notice in the Description page of Project Settings.

#include "SpringBumper.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"


// Sets default values
ASpringBumper::ASpringBumper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));
	SetRootComponent(Spring);

	Bumper = CreateDefaultSubobject<UStaticMeshComponent>(FName("Bumper"));
	Bumper->SetupAttachment(Spring);
}

// Called when the game starts or when spawned
void ASpringBumper::BeginPlay()
{
	Super::BeginPlay();
	
	SetupConstraint();

}

void ASpringBumper::SetupConstraint()
{
	if (!GetAttachParentActor()) return;
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) return;
	Spring->SetConstrainedComponents(BodyRoot, NAME_None, Bumper, NAME_None);
}

// Called every frame
void ASpringBumper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

