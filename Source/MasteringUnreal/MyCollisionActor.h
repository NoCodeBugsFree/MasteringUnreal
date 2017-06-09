// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MyCollisionActor.generated.h"

UCLASS()
class MASTERINGUNREAL_API AMyCollisionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyCollisionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	UPhysicalMaterial* PhysicalMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	TEnumAsByte<ECollisionResponse> ResponseToCollisionChannel = ECollisionResponse::ECR_Overlap;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
