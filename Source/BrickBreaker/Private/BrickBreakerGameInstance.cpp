// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickBreakerGameInstance.h"
#include <Kismet/GameplayStatics.h>

UBrickBreakerGameInstance::UBrickBreakerGameInstance()
{
    /*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Game Instance initialisation"));
    LoadScore();*/
}

void UBrickBreakerGameInstance::Init()
{
    Super::Init(); 
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Game Instance initialisation"));
    LoadScore(); 
}

void UBrickBreakerGameInstance::SaveScore()
{
    UGameplayStatics::SaveGameToSlot(SaveGameScoreRef, TEXT("BestScore"), 0);
}

void UBrickBreakerGameInstance::LoadScore()
{
    SaveGameScoreRef = Cast<USaveGameScore>(UGameplayStatics::LoadGameFromSlot(TEXT("BestScore"), 0));

    if (!SaveGameScoreRef)
    {
        SaveGameScoreRef = NewObject<USaveGameScore>();

        SaveGameScoreRef->Level1 = 0;
        SaveGameScoreRef->Level2 = 0;
        SaveGameScoreRef->Level3 = 0;
        SaveGameScoreRef->Level4 = 0;
        SaveGameScoreRef->Level5 = 0;

        SaveScore();
    }
}