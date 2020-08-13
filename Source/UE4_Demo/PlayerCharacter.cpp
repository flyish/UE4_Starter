// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplay/Public/HeadMountedDisplayFunctionLibrary.h"
#include "AIModule/Classes/AIController.h"
#include "Helper/HelperBlueprintFunctionLibrary.h"
#include "Components/LineBatchComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	baseTurnRate = 45.f;
	baseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(RootComponent);
	cameraBoom->TargetArmLength = 300;
	cameraBoom->bUsePawnControlRotation = true;

	followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	followCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);
	followCamera->bUsePawnControlRotation = false;

	//USceneComponent* pRootTemp = RootComponent;
	//USceneComponent* pRootNew = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerCharterRoot"));
	//RootComponent = pRootNew;
	//if (NULL != pRootTemp)
	//{
	//	pRootTemp->SetupAttachment(RootComponent);
	//}
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void APlayerCharacter::MoveForward(float Value)
{
	if (Controller != NULL && Value != 0.0f)
	{
		const FRotator& Rotation = Controller->GetControlRotation();
		const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis( EAxis::X );
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (Controller != NULL && Value != 0.0f)
	{
		const FRotator& Rotation = Controller->GetControlRotation();
		const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::TurnAtRate(float Value)
{
	AddControllerYawInput(Value * baseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Value)
{
	AddControllerPitchInput(Value * baseLookUpRate * GetWorld()->GetDeltaSeconds());

}

void APlayerCharacter::TouchStart(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void APlayerCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &APlayerCharacter::TouchStart);
	PlayerInputComponent->BindTouch(IE_Released, this, &APlayerCharacter::TouchStopped);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &APlayerCharacter::OnResetVR);
}

void APlayerCharacter::setSelActor(AActor* pSelActor)
{
	if (pSelActor != m_pSelActor)
	{
		m_pSelActor = pSelActor;

		clearBB();

		if (NULL != m_pSelActor)
		{
			FVector origin_;
			FVector boxExtent_;
			m_pSelActor->GetActorBounds(true, origin_, boxExtent_, true);
			TArray<FVector> vertices_ = makeBBVertices(origin_, boxExtent_);
			drawBB(vertices_, 0);
		}
	}
}

AActor* APlayerCharacter::getSelActor() const
{
	return m_pSelActor;
}

void APlayerCharacter::clearBB()
{
	UWorld* pWorld_ = UHelperBlueprintFunctionLibrary::playWorld();
	ULineBatchComponent* pLineBatchComp_ = pWorld_->PersistentLineBatcher;
	if (NULL != pLineBatchComp_)
	{
		pLineBatchComp_->Flush();
	}
}

void APlayerCharacter::drawBB(const TArray<FVector>& vertices, float duration)
{
	UWorld* pWorld_ = UHelperBlueprintFunctionLibrary::playWorld();
	ULineBatchComponent* const pLineBatchComp_ = pWorld_->PersistentLineBatcher;
	if (pLineBatchComp_ != NULL)
	{
		FVector v0 = vertices[0];
		FVector v1 = vertices[1];
		FVector v2 = vertices[2];
		FVector v3 = vertices[3];


		FVector v4 = vertices[4];
		FVector v5 = vertices[5];
		FVector v6 = vertices[6];
		FVector v7 = vertices[7];

		// top
		pLineBatchComp_->DrawLine(v0, v1, FLinearColor::Red, 10, 2, duration);
		pLineBatchComp_->DrawLine(v1, v2, FLinearColor::Red, 10, 2, duration);
		pLineBatchComp_->DrawLine(v2, v3, FLinearColor::Red, 10, 2, duration);
		pLineBatchComp_->DrawLine(v3, v0, FLinearColor::Red, 10, 2, duration);

		// bottom
		pLineBatchComp_->DrawLine(v4, v5, FLinearColor::Red, 10, 2, duration);
		pLineBatchComp_->DrawLine(v5, v6, FLinearColor::Red, 10, 2, duration);
		pLineBatchComp_->DrawLine(v6, v7, FLinearColor::Red, 10, 2, duration);
		pLineBatchComp_->DrawLine(v7, v4, FLinearColor::Red, 10, 2, duration);

		// left
		pLineBatchComp_->DrawLine(v0, v1, FLinearColor::Red, 10, 2, duration);
		pLineBatchComp_->DrawLine(v1, v5, FLinearColor::Red, 10, 2, duration);
		pLineBatchComp_->DrawLine(v5, v4, FLinearColor::Red, 10, 2, duration);
		pLineBatchComp_->DrawLine(v4, v0, FLinearColor::Red, 10, 2, duration);

		// right
		pLineBatchComp_->DrawLine(v3, v2, FLinearColor::Red, 10, 2, duration);
		pLineBatchComp_->DrawLine(v2, v6, FLinearColor::Red, 10, 2, duration);
		pLineBatchComp_->DrawLine(v6, v7, FLinearColor::Red, 10, 2, duration);
		pLineBatchComp_->DrawLine(v7, v3, FLinearColor::Red, 10, 2, duration);

		//front
		pLineBatchComp_->DrawLine(v1, v2, FLinearColor::Red, 10, 2, duration);
		pLineBatchComp_->DrawLine(v2, v6, FLinearColor::Red, 10, 2, duration);
		pLineBatchComp_->DrawLine(v6, v5, FLinearColor::Red, 10, 2, duration);
		pLineBatchComp_->DrawLine(v5, v1, FLinearColor::Red, 10, 2, duration);

		//back
		pLineBatchComp_->DrawLine(v0, v3, FLinearColor::Red, 10, 2, duration);
		pLineBatchComp_->DrawLine(v3, v7, FLinearColor::Red, 10, 2, duration);
		pLineBatchComp_->DrawLine(v7, v4, FLinearColor::Red, 10, 2, duration);
		pLineBatchComp_->DrawLine(v4, v0, FLinearColor::Red, 10, 2, duration);
	}
}

TArray<FVector> APlayerCharacter::makeBBVertices(const FVector& vOrigin, const FVector& vBoxExent)
{
	TArray<FVector> result;

	FVector v0;
	v0.X = vOrigin.X - vBoxExent.X;
	v0.Y = vOrigin.Y + vBoxExent.Y;
	v0.Z = vOrigin.Z + vBoxExent.Z;
	result.Add(v0);

	FVector v1;
	v1.X = vOrigin.X + vBoxExent.X;
	v1.Y = vOrigin.Y + vBoxExent.Y;
	v1.Z = vOrigin.Z + vBoxExent.Z;
	result.Add(v1);

	FVector v2;
	v2.X = vOrigin.X + vBoxExent.X;
	v2.Y = vOrigin.Y - vBoxExent.Y;
	v2.Z = vOrigin.Z + vBoxExent.Z;
	result.Add(v2);

	FVector v3;
	v3.X = vOrigin.X - vBoxExent.X;
	v3.Y = vOrigin.Y - vBoxExent.Y;
	v3.Z = vOrigin.Z + vBoxExent.Z;
	result.Add(v3);

	FVector v4;
	v4.X = vOrigin.X - vBoxExent.X;
	v4.Y = vOrigin.Y + vBoxExent.Y;
	v4.Z = vOrigin.Z - vBoxExent.Z;
	result.Add(v4);

	FVector v5;
	v5.X = vOrigin.X + vBoxExent.X;
	v5.Y = vOrigin.Y + vBoxExent.Y;
	v5.Z = vOrigin.Z - vBoxExent.Z;
	result.Add(v5);

	FVector v6;
	v6.X = vOrigin.X + vBoxExent.X;
	v6.Y = vOrigin.Y - vBoxExent.Y;
	v6.Z = vOrigin.Z - vBoxExent.Z;
	result.Add(v6);

	FVector v7;
	v7.X = vOrigin.X - vBoxExent.X;
	v7.Y = vOrigin.Y - vBoxExent.Y;
	v7.Z = vOrigin.Z - vBoxExent.Z;
	result.Add(v7);

	return result;
}

