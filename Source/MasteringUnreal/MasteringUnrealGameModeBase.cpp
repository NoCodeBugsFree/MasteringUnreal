// Fill out your copyright notice in the Description page of Project Settings.

#include "MasteringUnreal.h"
#include "MasteringUnrealGameModeBase.h"

AMasteringUnrealGameModeBase::AMasteringUnrealGameModeBase()
{
	PrimaryActorTick.bCanEverTick = false;


}

void AMasteringUnrealGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
// 	if (GEngine)
// 	{
// 		GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, FString::Printf(TEXT("version")));
// 	}

	Object = FVector2D::ZeroVector;
}

void AMasteringUnrealGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Object = TranslateObject(Object, FVector2D(0.1f, 0.1f));

// 	if (GEngine)
// 	{
// 		GEngine->AddOnScreenDebugMessage(0, 0.1f, FColor::Red, Object.ToString());
// 	}
}

FVector2D AMasteringUnrealGameModeBase::TranslateObject(FVector2D ObjectToTranslate, FVector2D ByAmount)
{
	FVector2D TranslatedObject = ObjectToTranslate + ByAmount;

// 	if (GEngine)
// 	{
// 		FString DebugString;
// 		
// 		DebugString = DebugString.Append(TEXT("Initial Value: "));
// 		DebugString = DebugString.Append(ObjectToTranslate.ToString());
// 		DebugString = DebugString.Append(TEXT(" | ByAmount: "));
// 		DebugString = DebugString.Append(ByAmount.ToString());
// 		DebugString = DebugString.Append(TEXT(" | OutVector: "));
// 		DebugString = DebugString.Append(TranslatedObject.ToString());
// 
// 
// 		GEngine->AddOnScreenDebugMessage(0, 0.1f, FColor::Purple, *DebugString);
// 	}

	return TranslatedObject;
}
