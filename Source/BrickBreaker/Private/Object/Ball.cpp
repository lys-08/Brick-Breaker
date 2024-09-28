// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Ball.h"
#include <Kismet/GameplayStatics.h>


// Sets default values
ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	// Sounds
	BrickCollisionSound = CreateDefaultSubobject<USoundBase>(TEXT("Brick Collision Sound"));
	WallCollisionSound = CreateDefaultSubobject<USoundBase>(TEXT("Wall Collision Sound"));
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
	// Setting the Paddle Reference
	PaddleRef = Cast<APaddle>(UGameplayStatics::GetActorOfClass(GetWorld(), APaddle::StaticClass()));

	StaticMesh->AddImpulse(FVector(-1200, 0, 0), NAME_None, true);
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

