// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Ball.h"
#include <Kismet/GameplayStatics.h>


// Sets default values
ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	StaticMesh->AddImpulse(FVector(-1000, 0, 0), NAME_None, true);
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}