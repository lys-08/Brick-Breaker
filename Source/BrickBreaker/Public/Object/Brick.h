// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Player/Paddle.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Brick.generated.h"

UCLASS()
class BRICKBREAKER_API ABrick : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere) APaddle* PaddleRef;

	// Materials
	UPROPERTY(EditAnywhere, Category = "Material") UMaterial* Mat1;
	UPROPERTY(EditAnywhere, Category = "Material") UMaterial* Mat2;
	UPROPERTY(EditAnywhere, Category = "Material") UMaterial* Mat3;

	// Niagara System
	UPROPERTY(EditDefaultsOnly, Category = "Niagara") UNiagaraSystem* NiagaraSystem1;
	UPROPERTY(EditDefaultsOnly, Category = "Niagara") UNiagaraSystem* NiagaraSystem2;
	UPROPERTY(EditDefaultsOnly, Category = "Niagara") UNiagaraSystem* NiagaraSystem3;
	UPROPERTY(EditDefaultsOnly, Category = "Niagara") UNiagaraSystem* CurrentNiagaraSystem;

	// Sounds
	UPROPERTY(EditDefaultsOnly, Category = "Sound") class USoundBase* BrickCollisionSound;
	
public:	
	UPROPERTY(EditAnywhere) int brickStrength = 1; // Brick strength = number of collision before destruction

	// ----- METHODS
	ABrick();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void UpdateBrickColor();
	void OnNiagaraFinished(UNiagaraComponent* NiagaraComponent);
	UFUNCTION() 
	void HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
