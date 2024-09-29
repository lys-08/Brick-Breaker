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

	// Setting the Ball Reference
	BallRef = Cast<ABall>(UGameplayStatics::GetActorOfClass(GetWorld(), ABall::StaticClass()));

	// Get Game Instance Ref
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Game Instance initialisation PADDLE"));
	BrickBreakerGM = Cast<UBrickBreakerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
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
		if (Lives == 0)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), LoseSound);

			BrickBreakerGM->SaveGameScoreRef->SaveLevelScore(GetWorld()->GetMapName(), Score);

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

		else
		{
			UGameplayStatics::PlaySound2D(GetWorld(), LostLifeSound);

			BallRef->StaticMesh->SetPhysicsLinearVelocity(FVector(0, 0, 0));
			BallRef->SetActorLocation(FVector(-400, 0, 30));

			UUserWidget* CountdownUserWidget = CreateWidget<UUserWidget>(GetWorld(), CountdownWidgetClass);
			if (CountdownUserWidget)
			{
				CountdownUserWidget->AddToViewport();
			}

			Countdown = 3;
			GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, [this, CountdownUserWidget]() { CountdownTick(CountdownUserWidget); }, 1.0f, true);
		}
	}
}

void APaddle::UpdateBrickNumber()
{
	BrickNumber--;

	if (BrickNumber == 0)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), WinSound);

		BrickBreakerGM->SaveGameScoreRef->SaveLevelScore(GetWorld()->GetMapName(), Score);

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

void APaddle::CountdownTick(UUserWidget* UserWidget)
{
	if (Countdown > 0)
	{
		Countdown--;
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);

		UserWidget->RemoveFromParent();
		BallRef->StaticMesh->SetPhysicsLinearVelocity(FVector(-800, 0, 0));
	}
}