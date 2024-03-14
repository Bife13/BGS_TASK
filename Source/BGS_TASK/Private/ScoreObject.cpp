// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreObject.h"

#include "Skating.h"
#include "SkatingGameMode.h"
#include "Components/BoxComponent.h"

// Sets default values
AScoreObject::AScoreObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(StaticMesh);
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AScoreObject::BeginPlay()
{
	Super::BeginPlay();
	SkatingGameMode = Cast<ASkatingGameMode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
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
		if (ISkating* SkatingInterface = Cast<ISkating>(OtherActor))
		{
			if (SkatingInterface->GetCharacterMovementComponent()->IsFalling())
			{
				SkatingGameMode->IncreaseScore(ObjectScore);
			}
		}
	}
}
