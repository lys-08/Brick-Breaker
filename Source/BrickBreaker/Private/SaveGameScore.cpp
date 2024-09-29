// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameScore.h"
#include <Kismet/GameplayStatics.h>

void USaveGameScore::SaveLevelScore(FString Level, int Score)
{
    Level.RemoveFromStart(TEXT("UEDPIE_0_"));

    if (Level == TEXT("Level_01"))
    {
        if (Score > Level1) Level1 = Score;
    }
    if (Level == TEXT("Level_02"))
    {
        if (Score > Level2) Level2 = Score;
    }
    if (Level == TEXT("Level_03"))
    {
        if (Score > Level3) Level3 = Score;
    }
    if (Level == TEXT("Level_04"))
    {
        if (Score > Level4) Level4 = Score;
    }
    if (Level == TEXT("Level_05"))
    {
        if (Score > Level5) Level5 = Score;
    }
}