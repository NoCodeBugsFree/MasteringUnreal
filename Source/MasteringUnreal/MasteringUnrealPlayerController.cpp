// Fill out your copyright notice in the Description page of Project Settings.

#include "MasteringUnreal.h"
#include "DrawDebugHelpers.h"
#include "MasteringUnrealPlayerController.h"

void AMasteringUnrealPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Fire", IE_Pressed, this, &AMasteringUnrealPlayerController::Fire);
}

void AMasteringUnrealPlayerController::Fire()
{
	/* Single Test

	float Distance = 100.f;

	FVector Direction = PlayerCameraManager->GetActorForwardVector();
	FVector Start = PlayerCameraManager->GetCameraLocation();
	FVector End = Start + (Direction * Distance);

	FHitResult OutHit;

	bool bHasHitSomething = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Camera);

	DrawDebugLine(GetWorld(), Start, End, FColor::Red, true, 10.f, (uint8)0, 10.f);
	*/
	
	float Distance = 4000.f;

	FVector Direction = PlayerCameraManager->GetActorForwardVector();
	FVector Start = PlayerCameraManager->GetCameraLocation() + (Direction * 40.f);
	FVector End = Start + (Direction * Distance);

	TArray<FHitResult> OutHits;
	bool bHasHitSomething = GetWorld()->LineTraceMultiByChannel(OutHits, Start, End, ECC_Camera);

	for (FHitResult& Elem : OutHits)
	{
		FColor Color = FColor::MakeRandomColor();

		FVector ImpactPoint = Elem.ImpactPoint;

		DrawDebugLine(GetWorld(), Start, ImpactPoint, Color, true, 10.f, 0, 10.f);

// 		if (GEngine)
// 		{
// 			GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, Elem.GetActor()->GetName());
// 		}
	}

}
