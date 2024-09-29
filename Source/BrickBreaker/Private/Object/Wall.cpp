// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Wall.h"
#include "Object/Ball.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AWall::AWall()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->OnComponentHit.AddDynamic(this, &AWall::HitMesh);
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWall::HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (auto Ball = Cast<ABall>(OtherActor))
	{
		UGameplayStatics::PlaySound2D(GetWorld(), WallCollisionSound);
	}
}