// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameScore.generated.h"

/**
 * 
 */
UCLASS()
class BRICKBREAKER_API USaveGameScore : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score") int Level1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score") int Level2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score") int Level3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score") int Level4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score") int Level5;

	void SaveLevelScore(FString Level, int Score);
};
