// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkatingGameMode.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "ScoreObject.generated.h"

UCLASS()
class BGS_TASK_API AScoreObject : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

public:	
	AScoreObject();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	ASkatingGameMode* SkatingGameMode;
	
	UPROPERTY()
	AActor* CurrentOverlappingActor;
	
	UPROPERTY(EditAnywhere,Category = Score)
	float ObjectScore;

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
};
