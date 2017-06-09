// Fill out your copyright notice in the Description page of Project Settings.

#include "MasteringUnreal.h"
#include "FireAnimNotify.h"
#include "GrannyAnimInstance.h"

void UFireAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UGrannyAnimInstance* GrannyAnimInstance = Cast<UGrannyAnimInstance>(MeshComp->GetAnimInstance());

	if (GrannyAnimInstance)
	{
		GrannyAnimInstance->Fire();
	}
}
