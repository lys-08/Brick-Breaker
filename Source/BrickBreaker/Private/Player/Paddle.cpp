// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Paddle.h"
#include "Object/Brick.h"
#include "Object/Ball.h"
#include "Blueprint/UserWidget.h"
#include "Components/Widget.h"
#include "GameFramework/FloatingPawnMovement.h"
#include <Kismet/GameplayStatics.h>

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
	StaticMesh->OnComponentHit.AddDynamic(this, &APaddle::HitMesh);
	
	// Count brick number
	TArray<AActor*> Bricks;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABrick::StaticClass(), Bricks);
	BrickNumber = Bricks.Num();
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

void APaddle::HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Paddle Hit"));
	if (auto Ball = Cast<ABall>(OtherActor))
	{
		UGameplayStatics::PlaySound2D(GetWorld(), PaddleCollisionSound);
	}
}

void APaddle::UpdateScore()
{
	Score += 100;
}

void APaddle::UpdateLife(int diff)
{
	Lives += diff;
	if (diff > 0)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), UpSound);
	}
	else
	{
		UGameplayStatics::PlaySound2D(GetWorld(), LostLifeSound);

		// Ball spawner
		//BallRef->SetActorLocation(FVector(-400, 0, 30));
		//BallRef->SetActorRotation(FRotator(0, 0, 0));

		/*FTransform SpawnTransform = FTransform(FRotator(0, 0, 0), FVector(-400, 0, 30));
		UWorld* MyLevel = GetWorld();
		ABall* SpawnedActor = MyLevel->SpawnActor<ABall>(ABall::StaticClass(), SpawnTransform);*/


		if (Lives == 0)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), LoseSound);

			UGameplayStatics::SetGamePaused(GetWorld(), true);
			UUserWidget* LoseUserWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverLoseWidgetClass);
			if (LoseUserWidget)
			{
				LoseUserWidget->AddToViewport();
				if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
				{
					PC->bShowMouseCursor = true;
					PC->SetInputMode(FInputModeUIOnly());
				}
			}
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Lives: %d"), Lives));
}

void APaddle::UpdateBrickNumber()
{
	BrickNumber--;

	if (BrickNumber == 0)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), WinSound);

		UGameplayStatics::SetGamePaused(GetWorld(), true);
		UUserWidget* WinUserWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWinWidgetClass);
		if (WinUserWidget)
		{
			WinUserWidget->AddToViewport();
			if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
			{
				PC->bShowMouseCursor = true;
				PC->SetInputMode(FInputModeUIOnly());
			}
		}
	}
}