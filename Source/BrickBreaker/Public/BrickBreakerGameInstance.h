// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SaveGameScore.h"
#include "BrickBreakerGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BRICKBREAKER_API UBrickBreakerGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) USaveGameScore* SaveGameScoreRef;
	
	UBrickBreakerGameInstance();
	virtual void Init() override;

	UFUNCTION(BlueprintCallable) void SaveScore();
	void LoadScore();
};
