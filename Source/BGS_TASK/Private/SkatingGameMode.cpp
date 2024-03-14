// Fill out your copyright notice in the Description page of Project Settings.


#include "SkatingGameMode.h"

void ASkatingGameMode::IncreaseScore(float Value)
{
	ScoreValue += Value;
	IncreaseScoreEvent();
}

