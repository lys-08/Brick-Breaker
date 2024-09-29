// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Brick.h"
#include "MovingBrick.generated.h"

/**
 * 
 */
UCLASS()
class BRICKBREAKER_API AMovingBrick : public ABrick
{
	GENERATED_BODY()

    FVector TargetLocation;

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    void MoveRandomly();    
};
