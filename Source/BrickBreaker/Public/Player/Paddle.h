// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TimerManager.h"
#include "../Object/Ball.h"
#include "BrickBreakerGameInstance.h"
#include "Paddle.generated.h"

UCLASS()
class BRICKBREAKER_API APaddle : public APawn
{
	GENERATED_BODY()

	// Sounds
	UPROPERTY(EditDefaultsOnly, Category = "Sound") class USoundBase* WinSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sound") class USoundBase* LoseSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sound") class USoundBase* LostLifeSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sound") class USoundBase* PaddleCollisionSound;

	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPawnMovementComponent* MovementComponent;

	ABall* BallRef;

	UBrickBreakerGameInstance* BrickBreakerGM;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

	// Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI") TSubclassOf<class UUserWidget> GameOverLoseWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI") TSubclassOf<class UUserWidget> GameOverWinWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI") TSubclassOf<class UUserWidget> CountdownWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) int Score = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int Lives = 3;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int BrickNumber;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) int Countdown;
	FTimerHandle CountdownTimerHandle;


	// Methods
	APaddle();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void MoveLeftRight(float AxisValue);
	void UpdateScore();
	void UpdateLife();
	void UpdateBrickNumber();
	void CountdownTick(UUserWidget* UserWidget);
};
