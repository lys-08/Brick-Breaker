// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

UCLASS()
class BRICKBREAKER_API ABall : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) class UStaticMeshComponent* StaticMesh;

	// Sounds
	UPROPERTY(EditDefaultsOnly) class USoundBase* BrickCollisionSound;
	UPROPERTY(EditDefaultsOnly) class USoundBase* WallCollisionSound;
	
public:	

	ABall();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION() 
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() 
	void HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
