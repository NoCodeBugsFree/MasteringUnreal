// Fill out your copyright notice in the Description page of Project Settings.

#include "MasteringUnreal.h"
#include "GrannyAnimInstance.h"
#include "BaseCharacter.h"

UGrannyAnimInstance::UGrannyAnimInstance()
{
	bIsInAir = false;
	bIsFiring = false;
	bIsBoxing = false;
}

void UGrannyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	APawn* TestPawn = TryGetPawnOwner();
	if (TestPawn)
	{
		ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(TestPawn);
		if (BaseCharacter)
		{
			// firing
			bIsFiring = BaseCharacter->GetIsFiring();
			
			// failing
			bIsInAir = BaseCharacter->GetMovementComponent()->IsFalling();

			// speed
			Speed = BaseCharacter->GetVelocity().Size();
		}
	}
}

void UGrannyAnimInstance::Fire()
{
	APawn* TestPawn = TryGetPawnOwner();
	if (TestPawn)
	{
		ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(TestPawn);
		if (BaseCharacter)
		{
			BaseCharacter->Fired();
		}
	}
}
