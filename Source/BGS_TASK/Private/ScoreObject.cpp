// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreObject.h"

#include "Skating.h"
#include "SkatingGameMode.h"
#include "Components/BoxComponent.h"

AScoreObject::AScoreObject()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(StaticMesh);
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetupAttachment(RootComponent);
}

void AScoreObject::BeginPlay()
{
	Super::BeginPlay();
	SkatingGameMode = Cast<ASkatingGameMode>(GetWorld()->GetAuthGameMode());
}

void AScoreObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AScoreObject::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	CurrentOverlappingActor = OtherActor;
}

void AScoreObject::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if (CurrentOverlappingActor == OtherActor)
	{
		if (OtherActor->Implements<USkating>())
		{
			if(ISkating::Execute_GetCharacterMovementComponent(OtherActor)->IsFalling())
				SkatingGameMode->IncreaseScore(ObjectScore);
		}
	}
}
