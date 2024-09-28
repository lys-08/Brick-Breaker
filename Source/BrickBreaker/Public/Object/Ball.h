// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Player/Paddle.h"
// #include "NiagaraSystem.h"
// #include "NiagaraComponent.h"
// #include "NiagaraFunctionLibrary.h"
#include "Ball.generated.h"

UCLASS()
class BRICKBREAKER_API ABall : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere) APaddle* PaddleRef;

	// Niagara System
	// UPROPERTY(EditDefaultsOnly, Category = "Niagara") UNiagaraSystem* NiagaraSystem1;
	// UPROPERTY(EditDefaultsOnly, Category = "Niagara") UNiagaraSystem* NiagaraSystem2;
	// UPROPERTY(EditDefaultsOnly, Category = "Niagara") UNiagaraSystem* NiagaraSystem3;

	// Sounds
	UPROPERTY(EditDefaultsOnly) class USoundBase* BrickCollisionSound;
	UPROPERTY(EditDefaultsOnly) class USoundBase* WallCollisionSound;
	
public:	

	ABall();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
