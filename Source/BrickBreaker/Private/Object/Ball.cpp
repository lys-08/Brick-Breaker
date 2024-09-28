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
	//StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ABall::OnOverlap);
	StaticMesh->OnComponentHit.AddDynamic(this, &ABall::HitMesh);

	StaticMesh->AddImpulse(FVector(-1200, 0, 0), NAME_None, true);
	//StaticMesh->SetPhysicsLinearVelocity(FVector(-800, 0, 0));
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABall::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Ball Overlap"));
	//if (auto rebound = Cast<ABrick>(OtherActor) || Cast<AWall>(OtherActor) || Cast<APaddlePawn>(OtherActor))
	//{

	//	if (auto wallPaddle = Cast<AWall>(OtherActor) || Cast<APaddlePawn>(OtherActor))
	//	{
	//		UGameplayStatics::PlaySound2D(GetWorld(), WallCollisionSound);
	//	}

	//	if (auto Brick = Cast<ABrick>(OtherActor))
	//	{
	//		PaddleRef->UpdateScore();
	//		FVector pos = Brick->GetActorLocation();
	//		switch (Brick->brickStrength)
	//		{
	//		case 1:
	//			if (NiagaraSystem1)
	//			{
	//				UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraSystem1, pos, FRotator::ZeroRotator);
	//				if (NiagaraComponent)
	//				{
	//					OnNiagaraFinished(NiagaraComponent);
	//				}
	//			}
	//			break;
	//		case 2:
	//			if (NiagaraSystem2)
	//			{
	//				UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraSystem2, pos, FRotator::ZeroRotator);
	//				if (NiagaraComponent)
	//				{
	//					OnNiagaraFinished(NiagaraComponent);
	//				}
	//			}
	//			break;
	//		case 3:
	//			if (NiagaraSystem3)
	//			{
	//				UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraSystem3, pos, FRotator::ZeroRotator);
	//				if (NiagaraComponent)
	//				{
	//					OnNiagaraFinished(NiagaraComponent);
	//				}
	//			}
	//			break;
	//		default:
	//			// Optionnel : Gérer les cas non couverts
	//			break;
	//		}
	//		Brick->brickStrength -= 1;
	//		Brick->UpdateBrickColor();
	//		UGameplayStatics::PlaySound2D(GetWorld(), BrickCollisionSound);
	//		if (Brick->brickStrength == 0)
	//		{
	//			PaddleRef->UpdateBrickNumber();
	//			Brick->SetLifeSpan(0.08f);
	//		}
	//	}
	//}

	//if (auto barrier = Cast<ABarrier>(OtherActor))
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Barrier"));

	//	PaddleRef->UpdateLife(-1);
	//	SetActorLocation(FVector(-400, 0, 30));
	//	StaticMesh->SetPhysicsLinearVelocity(FVector(-800.0f, 0.0f, 0.0f));
	//	//Destroy();

	//}
}

void ABall::HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Ball Hit"));
	/*if (auto Ball = Cast<ABall>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This message will appear on the screen!"));
	}*/
}