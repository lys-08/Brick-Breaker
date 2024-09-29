// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/RotationWall.h"


void ARotationWall::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CurrentAngle += RotationSpeed * DeltaTime;
    if (CurrentAngle >= 360.0f)
    {
        CurrentAngle -= 360.0f;
    }

    // New Position
    float TotalAngle = InitialAngle + CurrentAngle;
    float Radians = FMath::DegreesToRadians(TotalAngle);
    FVector NewLocation = CenterPoint->GetActorLocation() + FVector(FMath::Cos(Radians), FMath::Sin(Radians), 0) * Radius;

    SetActorLocation(NewLocation);
}