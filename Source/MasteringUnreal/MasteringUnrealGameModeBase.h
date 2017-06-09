// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "MasteringUnrealGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MASTERINGUNREAL_API AMasteringUnrealGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	AMasteringUnrealGameModeBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

protected:



private:
	
	FVector2D Object;

	FVector2D TranslateObject(FVector2D ObjectToTranslate, FVector2D ByAmount);
	
};
