// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Brick.h"
#include "Object/Ball.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ABrick::ABrick()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->OnComponentHit.AddDynamic(this, &ABrick::HitMesh);

	// Setting the Paddle Reference
	PaddleRef = Cast<APaddle>(UGameplayStatics::GetActorOfClass(GetWorld(), APaddle::StaticClass()));

	UpdateBrickColor();
}

// Called every frame
void ABrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABrick::UpdateBrickColor()
{
	switch (brickStrength)
	{
	case 1:
		StaticMesh->SetMaterial(0, Mat1);
		CurrentNiagaraSystem = NiagaraSystem1;
		break;
	case 2:
		StaticMesh->SetMaterial(0, Mat2);
		CurrentNiagaraSystem = NiagaraSystem2;
		break;
	case 3:
		StaticMesh->SetMaterial(0, Mat3);
		CurrentNiagaraSystem = NiagaraSystem3;
		break;
	}
}

void ABrick::OnNiagaraFinished(UNiagaraComponent* NiagaraComponent)
{
	FTimerHandle DestroyTimerHandle;

	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle,
		[NiagaraComponent]()
		{
			if (NiagaraComponent)
			{
				NiagaraComponent->DestroyComponent();
			}
		},
		2.0f,
		false);
}

void ABrick::HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Brick Hit"));
	if (auto Ball = Cast<ABall>(OtherActor))
	{
		PaddleRef->UpdateScore();

		UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), CurrentNiagaraSystem, GetActorLocation(), FRotator::ZeroRotator);
		if (NiagaraComponent)
		{
			OnNiagaraFinished(NiagaraComponent);
		}

		brickStrength -= 1;
		UpdateBrickColor();
		UGameplayStatics::PlaySound2D(GetWorld(), BrickCollisionSound);

		if (brickStrength == 0)
		{
			PaddleRef->UpdateBrickNumber();
			Destroy();
		}
	}
}