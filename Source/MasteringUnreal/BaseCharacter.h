// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class MASTERINGUNREAL_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called in appropriate time from UGrannyAnimInstance::Fire()  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void Fired();

	/** Returns bIsFiring state  */
	UFUNCTION(BlueprintPure, Category = "AAA")
	bool GetIsFiring() const { return bIsFiring; };

	/** sets jogging/running animation speed  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetAnimationPlayRate(float NewPlayRate);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	bool bIsFiring;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	bool bIsSprinting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	float MaxSprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	float BaseRunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	float TimeToMaxSpeed;
	
	float CurrentSprint;

private:

	void MoveRight(float Amount);
	void MoveForward(float Amount);
	void RotateCamera(float Amount);
	void ChangeCameraHeight(float Amount);

	void SprintStart();
	void SprintEnd();

	void FireStart();

	
	
	/** Camera Boom  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Camera  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	/** Forward Direction  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ForwardDirection;

	/** Explosion Effect  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* ExplosionEffect;
	
public:
	
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	FORCEINLINE UCameraComponent* GetCameraComponent() const { return Camera; }
	
	FORCEINLINE UArrowComponent* GetArrowComponent() const { return ForwardDirection; }

};
