// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Paddle.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
APaddle::APaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("MovementComponent0"));
	MovementComponent->UpdatedComponent = StaticMesh;
}

// Called when the game starts or when spawned
void APaddle::BeginPlay()
{
	Super::BeginPlay();
	
	// Count brick number
	// TArray<AActor*> Bricks;
	// UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABrick::StaticClass(), Bricks);
	// BrickNumber = Bricks.Num();
}

// Called every frame
void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind Axis
	PlayerInputComponent->BindAxis(TEXT("MoveLeftRight"), this, &APaddle::MoveLeftRight);
}

void APaddle::MoveLeftRight(float AxisValue)
{
	FVector Direction = FVector(0, 1, 0);
	AddMovementInput(Direction, AxisValue);
}