// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Ball.h"
#include <Kismet/GameplayStatics.h>


ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
}

void ABall::BeginPlay()
{
	Super::BeginPlay();

	StaticMesh->AddImpulse(FVector(-1000, 0, 0), NAME_None, true);
	MaxSpeed = FVector(-1000, 0, 0).Size();
	MinSpeed = FVector(-900, 0, 0).Size();
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentVelocity = StaticMesh->GetComponentVelocity();
	float CurrentSpeed = CurrentVelocity.Size();

	if (CurrentSpeed > MaxSpeed)
	{
		FVector NewVelocity = CurrentVelocity.GetSafeNormal() * MaxSpeed;
		StaticMesh->SetPhysicsLinearVelocity(NewVelocity);
	}
	if (CurrentSpeed < MinSpeed)
	{
		FVector NewVelocity = CurrentVelocity.GetSafeNormal() * MinSpeed;
		StaticMesh->SetPhysicsLinearVelocity(NewVelocity);
	}
}