// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/Interface.h"
#include "Skating.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class USkating : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BGS_TASK_API ISkating
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	UCharacterMovementComponent* GetCharacterMovementComponent();
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	float GetMovementInput();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetTurnInput();
};
