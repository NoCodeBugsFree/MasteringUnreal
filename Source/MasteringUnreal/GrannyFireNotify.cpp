// Fill out your copyright notice in the Description page of Project Settings.

#include "MasteringUnreal.h"
#include "GrannyFireNotify.h"
#include "GrannyAnimInstance.h"




void UGrannyFireNotifyState::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	UGrannyAnimInstance* GrannyAnimInstance = Cast<UGrannyAnimInstance>(MeshComp->GetAnimInstance());

	if (GrannyAnimInstance)
	{
		GrannyAnimInstance->Fire();
	}
}

void UGrannyFireNotifyState::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	UE_LOG(LogTemp, Error, TEXT("NotifyTick cpp"));
}

void UGrannyFireNotifyState::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	UE_LOG(LogTemp, Error, TEXT("NotifyEnd cpp"));
}
