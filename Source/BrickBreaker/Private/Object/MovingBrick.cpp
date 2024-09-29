// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/MovingBrick.h"

void AMovingBrick::BeginPlay()
{
    Super::BeginPlay();
    MoveRandomly();
}

void AMovingBrick::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (FVector::Dist(GetActorLocation(), TargetLocation) < 10.0f) 
    {
        MoveRandomly();
    }

    SetActorLocation(FMath::VInterpTo(GetActorLocation(), TargetLocation, DeltaTime, 1.0f));
}


void AMovingBrick::MoveRandomly()
{
    float X = FMath::RandRange(-250, 400);
    float Y = FMath::RandRange(-1000, 1000);
    TargetLocation = FVector(X, Y, GetActorLocation().Z);
}