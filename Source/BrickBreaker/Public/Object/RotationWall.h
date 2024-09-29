// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Wall.h"
#include "RotationWall.generated.h"

/**
 * 
 */
UCLASS()
class BRICKBREAKER_API ARotationWall : public AWall
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Rotation") AActor* CenterPoint;
	UPROPERTY(EditAnywhere, Category = "Rotation") float RotationSpeed = 45.0f;
	UPROPERTY(EditAnywhere, Category = "Rotation") float Radius = 200.0f;

	float CurrentAngle = 0.0f;
	UPROPERTY(EditAnywhere) float InitialAngle = 0.0f;

public:
	virtual void Tick(float DeltaTime) override;
};
