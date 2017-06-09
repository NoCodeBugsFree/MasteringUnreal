// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "GrannyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MASTERINGUNREAL_API UGrannyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UGrannyAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "AAA")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetPlayRate(float NewPlayRate) { PlayRate = NewPlayRate; }

	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetIsBoxing(bool NewBoxing) { bIsBoxing = NewBoxing; }

protected:



private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	uint32 bIsInAir : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	uint32 bIsFiring : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	uint32 bIsBoxing : 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float PlayRate = 1.f;
	
};
