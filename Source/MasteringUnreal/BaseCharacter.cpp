// Fill out your copyright notice in the Description page of Project Settings.

#include "MasteringUnreal.h"
#include "BaseCharacter.h"
#include "GrannyAnimInstance.h"


// Sets default values
ABaseCharacter::ABaseCharacter() 
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bAbsoluteRotation = true;
	CameraBoom->TargetArmLength = 1000.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);
	Camera->FieldOfView = 110.f;

	ForwardDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("ForwardDirection"));
	ForwardDirection->SetupAttachment(RootComponent);

	// turn off collision for out raycasts on our mesh
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Destructible, ECollisionResponse::ECR_Ignore);
	

	bIsFiring = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->SetWalkableFloorAngle(50.f);
	GetCharacterMovement()->MaxStepHeight = 45.f;

	ExplosionEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionEffect"));
	ExplosionEffect->bAutoActivate = false;
	ExplosionEffect->SetCollisionResponseToChannel(ECC_Destructible, ECR_Ignore);

	// Mario jump mechanic
	JumpMaxHoldTime = 0.5f;
	GetCharacterMovement()->AirControl = 0.5f;
	GetCharacterMovement()->JumpZVelocity = 800.f;
	GetCharacterMovement()->GravityScale = 2.f;

	// support double jump
	JumpMaxCount = 2;

	// 
	bIsSprinting = false;
	BaseRunSpeed = 600.f;
	MaxSprint = 2.f;
	CurrentSprint = 1.f;
	GetCharacterMovement()->MaxWalkSpeed = BaseRunSpeed;
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Actions
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABaseCharacter::FireStart);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ABaseCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ABaseCharacter::SprintEnd);

	// Axis
	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("RotateCamera", this, &ABaseCharacter::RotateCamera);
	PlayerInputComponent->BindAxis("ChangeCameraHight", this, &ABaseCharacter::ChangeCameraHeight);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CameraBoom->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.f, -25.f, 0.f)));
}

void ABaseCharacter::MoveRight(float Amount)
{
	if (Controller && Amount && !bIsFiring)
	{
		AddMovementInput(GetCameraBoom()->GetRightVector(), Amount);
	}
}

void ABaseCharacter::MoveForward(float Amount)
{
	if (Controller && Amount && !bIsFiring)
	{
		AddMovementInput(GetCameraBoom()->GetForwardVector(), Amount);
	}
}

void ABaseCharacter::RotateCamera(float Amount)
{
	if (Controller && Amount)
	{
 		FVector Rotation = GetCameraBoom()->GetComponentRotation().Euler();
 
 		Rotation += FVector(0.f, 0.f, Amount);
 
 		GetCameraBoom()->SetWorldRotation(FQuat::MakeFromEuler(Rotation));
	}
}

void ABaseCharacter::ChangeCameraHeight(float Amount)
{
	if (Controller && Amount)
	{
		FVector Rotation = GetCameraBoom()->GetComponentRotation().Euler();

		float NewHeight = Rotation.Y;
		NewHeight += Amount;
		NewHeight = FMath::Clamp(NewHeight, -45.f, -5.f);
		Rotation = FVector(0.f, NewHeight, Rotation.Z);
		GetCameraBoom()->SetWorldRotation(FQuat::MakeFromEuler(Rotation));
	}
}

void ABaseCharacter::SprintStart()
{
	bIsSprinting = true;
	SetAnimationPlayRate(1.6f);
}

void ABaseCharacter::SprintEnd()
{
	bIsSprinting = false;
	SetAnimationPlayRate(1.f);
}

void ABaseCharacter::FireStart()
{
	if (!bIsFiring)
	{
		bIsFiring = true;
	}
}

void ABaseCharacter::SetAnimationPlayRate(float NewPlayRate)
{
	UGrannyAnimInstance* GrannyAnimInstance =  Cast<UGrannyAnimInstance>(GetMesh()->GetAnimInstance());
	if (GrannyAnimInstance)
	{
		GrannyAnimInstance->SetPlayRate(NewPlayRate);
	}
}

void ABaseCharacter::Fired()
{
	if (!bIsFiring)
	{
		return;
	}

	// tell the engine that we've eaten the call to Fired()
	bIsFiring = false;

	FVector HandLocation = GetMesh()->GetBoneLocation(FName("LeftHandMiddle1"));

	if (ExplosionEffect)
	{
		ExplosionEffect->SetWorldLocation(HandLocation);
		ExplosionEffect->Activate(true);
	}

	float Distance = 10000.f;
	FVector Direction = GetArrowComponent()->GetForwardVector();
	FVector Start = HandLocation;
	FVector End = Start + (Direction * Distance);

	FHitResult OutHit;
	bool bHasHitSomething = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Destructible);

	FColor Color = FColor::MakeRandomColor();

	if (bHasHitSomething)
	{
		DrawDebugLine(GetWorld(), Start, OutHit.ImpactPoint, Color, true, 1.f, 0, 12.333);

		if (!OutHit.GetActor() || !OutHit.GetActor()->IsRootComponentMovable())
		{
			return;
		}

		TArray<UStaticMeshComponent*> Components;

		OutHit.GetActor()->GetComponents<UStaticMeshComponent>(Components);
		
		for (auto& TestMesh : Components)
		{
			TestMesh->AddForce(Direction * 100000000.f);
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), Start, End, Color, true, 1.f, 0, 12.333);
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float RampThisFrame = (DeltaTime / TimeToMaxSpeed) * MaxSprint;

	if (bIsSprinting)
	{
		CurrentSprint += RampThisFrame;
	} 
	else
	{
		CurrentSprint -= RampThisFrame;
	}

	CurrentSprint = FMath::Clamp(CurrentSprint, 1.f, MaxSprint);

	GetCharacterMovement()->MaxWalkSpeed = BaseRunSpeed * CurrentSprint;
}



