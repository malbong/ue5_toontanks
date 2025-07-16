// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
    Super::BeginPlay();

    PlayerController = Cast<APlayerController>(GetController());

    bAlive = true;

    OnTakeAnyDamage.AddDynamic(this, &ATank::TakenDamage);
}

void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (PlayerController)
    {
        FHitResult HitResult;
        bool HasHit = PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
        if (HasHit)
        {
            RotateTurret(HitResult.ImpactPoint);
        }
    }
}

void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

    PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ATank::Fire);
}

void ATank::HandleDestroy()
{
    Super::HandleDestroy();

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);

    bAlive = false;
}

void ATank::TakenDamage(AActor *DamagedActor,
                        float Damage,
                        const class UDamageType *DamageType,
                        class AController *InstigatedBy,
                        AActor *DamageCauser)
{
    if (PlayerController)
    {
        PlayerController->ClientStartCameraShake(OnHitCameraShakeClassType);
    }
}

void ATank::MoveForward(float Value)
{
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

    FVector DeltaLocalLocation = FVector::ZeroVector;
    DeltaLocalLocation.X = Value * DeltaTime * MoveSpeed;

    AddActorLocalOffset(DeltaLocalLocation, true);
}

void ATank::Turn(float Value)
{
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

    FRotator DeltaLocalRotation = FRotator::ZeroRotator;
    DeltaLocalRotation.Yaw = Value * DeltaTime * TurnRate;

    AddActorLocalRotation(DeltaLocalRotation, true);
}