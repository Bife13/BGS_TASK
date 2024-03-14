// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SkatingGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BGS_TASK_API ASkatingGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	float ScoreValue;

	UFUNCTION(BlueprintCallable)
	void IncreaseScore(float Value);

	UFUNCTION(BlueprintImplementableEvent)
	void IncreaseScoreEvent();
};
