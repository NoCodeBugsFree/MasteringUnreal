// Fill out your copyright notice in the Description page of Project Settings.

#include "MasteringUnreal.h"
#include "MyCollisionActor.h"


// Sets default values
AMyCollisionActor::AMyCollisionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;

	CollisionSphere->SetSphereRadius(32.f);
	CollisionSphere->SetVisibility(true);
	CollisionSphere->bHiddenInGame = false;
	CollisionSphere->SetSimulatePhysics(true);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//CollisionSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Block);
	CollisionSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
}

// Called when the game starts or when spawned
void AMyCollisionActor::BeginPlay()
{
	Super::BeginPlay();

	if (PhysicalMaterial)
	{
		CollisionSphere->BodyInstance.SetPhysMaterialOverride(PhysicalMaterial);
	}

	CollisionSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ResponseToCollisionChannel);
}

// Called every frame
void AMyCollisionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

